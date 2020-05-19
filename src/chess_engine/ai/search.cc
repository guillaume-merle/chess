#include <limits>
#include <algorithm>
#include <fstream>

#include "evaluation.hh"
#include "search.hh"
#include "logger.hh"
#include "move-ordering.hh"

Logger logger;

namespace ai
{
    Search::Search()
        : board_(), us_(board_.current_color()), time_(4)
    {}

    Chessboard& Search::get_board()
    {
        return board_;
    }

    Move& Search::get_bestmove()
    {
        return bestmove_;
    }

    int Search::quiesce_(Chessboard& board, int alpha, int beta, bool maximize)
    {
        int stand_pat = evaluate(board);

        if (stand_pat >= beta)
            return beta;

        if (alpha < stand_pat)
            alpha = stand_pat;

        std::vector<Move> captures = board.generate_legal_captures();

        auto move_ordering = MoveOrdering(captures, heuristics_);

        int score = 0;

        for (auto& capture : move_ordering.get())
        {
            Chessboard temp_board = board;
            temp_board.do_move(capture);

            score = -quiesce_(temp_board, -beta, -alpha, maximize);

            if (score >= beta)
                return beta;

            if (score > alpha)
                alpha = score;
        }

        return alpha;
    }

    int Search::minimax_(Chessboard& board, int depth, int alpha, int beta,
                         bool maximize)
    {
        if (std::chrono::system_clock::now() - start_ > time_)
        {
            timeout_ = true;
            return maximize ? alpha : beta;
        }

        // TODO: If board key has already existed 2 times then return 0

        // depth 0 changed the maximize / minimize,
        // need to evaluate for the last playing side with the right value.
        if (depth == 0)
        {
            //return quiesce_(board, alpha, beta, not maximize);
            if (maximize)
                return -evaluate(board);
            else
                return evaluate(board);
        }

        int bestscore;

        if (maximize)
            bestscore = std::numeric_limits<int>::min();
        else
            bestscore = std::numeric_limits<int>::max();

        std::vector<Move> moves = board.generate_legal_moves();

        if (moves.empty())
        {
            if (board.is_check(board.current_color()))
            {
                if (maximize)
                    return std::numeric_limits<int>::min();
                else
                    return std::numeric_limits<int>::max();
            }
            return 0;
        }

        auto move_ordering = MoveOrdering(moves, heuristics_,
                                          deep_depth_ - depth);

        for (auto& move : move_ordering.get())
        {
            Chessboard new_board = Chessboard(board);
            new_board.do_move(move);

            // TODO: Add board to the map
            int score = minimax_(new_board, depth - 1, alpha, beta, !maximize);
            // TODO: remove the board from the map

            if (timeout_)
                break;

            if (maximize)
            {
                bestscore = std::max(score, bestscore);
                alpha = std::max(alpha, bestscore);
            }
            else
            {
                bestscore = std::min(score, bestscore);
                beta = std::min(beta, bestscore);
            }

            if (alpha >= beta)
            {
                // get the killer moves from the real depth
                heuristics_.set_killer(move, deep_depth_ - depth);
                break;
            }
        }

        return bestscore;
    }

    Move Search::minimax_start_(int depth)
    {
        int bestscore = std::numeric_limits<int>::min();

        int alpha = std::numeric_limits<int>::min();
        int beta = std::numeric_limits<int>::max();

        std::vector<Move> moves = board_.generate_legal_moves();

        auto move_ordering = MoveOrdering(moves, heuristics_,
                                          deep_depth_ - depth);
        Move bestmove = moves.at(0);

        int score;

        for (auto& move : move_ordering.get())
        {
            Chessboard new_board = board_;
            new_board.do_move(move);

            score = minimax_(new_board, depth, alpha, beta, false);
            if (timeout_)
                break;

            if (score > bestscore)
            {
                bestscore = score;
                bestmove = move;
            }

            alpha = std::max(alpha, bestscore);
        }

        logger << "score: " << bestscore << ", depth: " << depth << "\n";

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
            current_best = minimax_start_(deep_depth_);

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

} // namespace board
