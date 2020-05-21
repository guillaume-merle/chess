#include <limits>
#include <algorithm>
#include <fstream>

#include "evaluation.hh"
#include "search.hh"
#include "logger.hh"
#include "move-ordering.hh"
#include "zobrist.hh"

Logger logger;

namespace ai
{
    Search::Search()
        : board_(), us_(board_.current_color()), time_(2)
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

        auto move_ordering = MoveOrdering(captures, heuristics_);

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

        std::vector<Move> moves = board.generate_legal_moves();

        if (moves.empty())
        {
            if (board.is_check(board.current_color()))
            {
                return -INF + 100 - depth;
            }
            return 0;
        }

        if (depth == 0)
        {
            return quiesce_(board, alpha, beta);
            //return evaluate(board);
        }

        auto move_ordering = MoveOrdering(moves, heuristics_,
                                          deep_depth_ - depth);

        for (auto& move : move_ordering.get())
        {
            Chessboard new_board = Chessboard(board);
            new_board.do_move(move);

            int score = -negamax_(new_board, depth - 1, -beta, -alpha);

            if (timeout_)
                break;

            if (score >= beta)
            {
                // set the killer moves for the real depth
                heuristics_.set_killer(move, deep_depth_ - depth);
                return beta;
            }

            if (score > alpha)
                alpha = score;
        }

        return alpha;
    }

    Move Search::negamax_start_(int depth)
    {
        int alpha = -INF;
        int beta = INF;

        std::vector<Move> moves = board_.generate_legal_moves();

        if (moves.empty())
            return Move();

        auto move_ordering = MoveOrdering(moves, heuristics_,
                                          deep_depth_ - depth);
        Move bestmove = moves.at(0);

        int score;

        for (auto& move : move_ordering.get())
        {
            Chessboard new_board = board_;
            new_board.do_move(move);

            score = -negamax_(new_board, depth - 1, -beta, -alpha);

            if (timeout_)
                break;

            if (score > alpha)
            {
                alpha = score;
                bestmove = move;
                if (score == INF)
                    break;
            }
        }

        logger << "score: " << alpha << ", depth: " << depth << "\n";

        return bestmove;
    }

    Move Search::find_move()
    {
        new_search();
        logger << "\nstart\n";
        Move current_best;

        for (int deep = 0; ; deep += 1)
        {
            bestmove_ = current_best;
            deep_depth_ = base_depth_ + deep;
            current_best = negamax_start_(deep_depth_);

            if (timeout_)
            {
                logger << "bestmove: " << bestmove_.to_string()
                       << ", depth: " << deep_depth_ - 1 << "\n";
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
        heuristics_ = MoveHeuristics();
    }

    bool Search::threefold_repetition(Chessboard& board)
    {
        auto it = board_dispositions_.find(board.get_zobrist_key().get());

        if (it != board_dispositions_.end() and it->second >= 3)
            return true;

        return false;
    }

} // namespace board
