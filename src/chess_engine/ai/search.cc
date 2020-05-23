#include <limits>
#include <algorithm>
#include <fstream>

#include "evaluation.hh"
#include "search.hh"
#include "logger.hh"
#include "move-ordering.hh"
#include "zobrist.hh"
#include "ttable-entry.hh"
#include "uci.hh"

Logger logger;

namespace ai
{
    Search::Search()
        : board_(), us_(board_.current_color()), time_(2000)
          , heuristics_(&ttable_)
    {
        board_.register_dispositions_history(&board_dispositions_);
    }

    Chessboard& Search::get_board()
    {
        return board_;
    }

    Move& Search::get_bestmove()
    {
        return bestmove_;
    }

    std::map<uint64_t, int>::iterator
    Search::add_board_disposition(uint64_t zobrist_key)
    {
        auto it = board_dispositions_.find(zobrist_key);

        if (it == board_dispositions_.end())
        {
            it = board_dispositions_.insert(it,
                                     std::pair<uint64_t, int>(zobrist_key, 1));
        }
        else
        {
            it->second += 1;
        }

        return it;
    }

    int Search::quiesce_(Chessboard& board, int alpha, int beta)
    {
        int stand_pat = evaluate(board);

        if (stand_pat >= beta)
            return beta;

        if (alpha < stand_pat)
            alpha = stand_pat;

        std::vector<Move> captures = board.generate_legal_captures();

        if (captures.empty())
            return stand_pat;

        auto move_ordering = MoveOrdering(captures, heuristics_, board);

        int score = 0;

        for (auto& capture : move_ordering.get())
        {
            Chessboard temp_board = board;
            temp_board.do_move(capture);

            score = -quiesce_(temp_board, -beta, -alpha);

            if (score >= beta)
                return score;

            if (score > alpha)
                alpha = score;
        }

        return alpha;
    }

    int Search::negamax_(Chessboard& board, int depth, int alpha, int beta)
    {
        if (std::chrono::system_clock::now() - start_ > time_)
        {
            timeout_ = true;
            // return value not use because of timeout
            return alpha;
        }

        // threefold repetition, 50 turns, and special dispositions
        if (board.is_draw())
        {
            return 0;
        }

        int alpha_base = alpha;

        auto entry = ttable_.at(board.get_zobrist_key(), depth);

        if (entry)
        {
            auto entry_score = entry->get_bounded_score(alpha, beta);
            if (entry_score)
                return entry_score.value();
        }

        std::vector<Move> moves = board.generate_legal_moves();

        if (moves.empty())
        {
            if (board.is_check(board.current_color()))
            {
                return -INF + (deep_depth_ - depth);
            }
            return 0;
        }

        if (depth == 0)
        {
            return quiesce_(board, alpha, beta);
            //return evaluate(board);
        }

        auto move_ordering = MoveOrdering(moves, heuristics_, board,
                                          deep_depth_ - depth);

        Move bestmove = move_ordering.get().at(0);

        for (auto& move : move_ordering.get())
        {
            Chessboard new_board = Chessboard(board);
            new_board.do_move(move);

            int score = -negamax_(new_board, depth - 1, -beta, -alpha);

            if (timeout_)
                break;

            // beta cut-off
            if (score >= beta)
            {
                // set the killer moves for the real depth
                heuristics_.set_killer(move, deep_depth_ - depth);

                // history heuristics on non capture moves
                if (not move.is_capture())
                    heuristics_.set_history(board.current_color(), move, depth);

                ttable_.insert(board.get_zobrist_key(), depth, score,
                               ALPHA, move);
                return beta;
            }

            if (score > alpha)
            {
                alpha = score;
                bestmove = move;
            }
        }

        if (alpha <= alpha_base)
            ttable_.insert(board.get_zobrist_key(), depth,
                           alpha, BETA, bestmove);
        else
            ttable_.insert(board.get_zobrist_key(), depth,
                           alpha, EXACT, bestmove);

        return alpha;
    }

    Move Search::negamax_start_(int depth)
    {
        int alpha = -INF;
        int beta = INF;

        std::vector<Move> moves = board_.generate_legal_moves();

        if (moves.empty())
            return Move();

        auto move_ordering = MoveOrdering(moves, heuristics_, board_,
                                          deep_depth_ - depth);
        Move bestmove = moves.at(0);

        int score;

        for (auto& move : move_ordering.get())
        {
            Chessboard new_board = board_;
            new_board.do_move(move);

            score = -negamax_(new_board, depth - 1, -beta, -alpha);

            // the search is null
            if (timeout_)
                return bestmove;

            if (score > alpha)
            {
                alpha = score;
                bestmove = move;

                // Checkmate found
                if (score > INF - 100)
                    break;
            }
        }

        // insert the move inside the transposition table
        ttable_.insert(board_.get_zobrist_key(), depth, alpha, EXACT,
                       bestmove);

        log_search(deep_depth_, alpha,
                   ttable_.principal_variation(board_, depth));

        bestscore_ = alpha;

        return bestmove;
    }

    Move Search::find_move()
    {
        new_search();
        Move current_best;

        for (int deep = 0; ; deep += 1)
        {
            bestmove_ = current_best;
            deep_depth_ = base_depth_ + deep;
            current_best = negamax_start_(deep_depth_);

            if (bestscore_ > INF - 100)
                return current_best;

            if (timeout_)
            {
                // if no bestmove was found, set bestmove to the move
                // returned by the interrupted minimax
                if (bestmove_.is_none())
                    bestmove_ = current_best;

                break;
            }
        }

        return bestmove_;
    }

    void Search::new_search()
    {
        timeout_ = false;
        start_ = std::chrono::system_clock::now();
        heuristics_ = MoveHeuristics(&ttable_);
        ttable_.clear();
        compute_time();
    }

    bool Search::threefold_repetition(Chessboard& board)
    {
        auto it = board_dispositions_.find(board.get_zobrist_key());

        if (it != board_dispositions_.end() and it->second >= 3)
            return true;

        return false;
    }

    void Search::compute_time()
    {
        int turn = board_.get_turn();

        float computed_time = 0.0;

        if (total_elapsed_time_ <= std::chrono::seconds(15))
        {
            computed_time = 0.5;
        }
        else if (total_elapsed_time_ <= std::chrono::seconds(30))
        {
            computed_time = 1.0;
        }
        else if (total_elapsed_time_ <= std::chrono::seconds(45))
        {
            computed_time = 1.5;
        }
        else
        {
            if (turn < 15)
                computed_time = 3.0 + turn / 7.0;
            else if (turn >= 15 and turn <= 25)
                computed_time = 8.0 - (std::abs(turn - 20.0) / 5.0);
            else if (turn > 25 and turn <= 55)
                computed_time = 5.0 - ((turn - 25.0) / 10.0);
            else if (turn > 55)
                computed_time = 2.0;
        }

        int computed_milliseconds = computed_time * 1000.0;
        time_ = std::chrono::milliseconds{computed_milliseconds};

        total_elapsed_time_ -= time_;
    }

} // namespace board
