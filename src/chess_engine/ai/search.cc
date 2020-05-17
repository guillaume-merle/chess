#include <limits>
#include <algorithm>
#include <fstream>

#include "evaluation.hh"
#include "search.hh"

namespace ai
{
    Search::Search()
        : board_(), us_(board_.current_color()), time_(1)
    {}

    Chessboard& Search::get_board()
    {
        return board_;
    }

    Move& Search::get_bestmove()
    {
        return bestmove_;
    }

    int Search::minimax_(Chessboard& board, int depth, int alpha, int beta,
                         bool maximize)
    {
        if (std::chrono::system_clock::now() - start_ > time_)
        {
            timeout_ = true;
            return maximize ? alpha : beta;
        }

        // depth 0 changed the maximize / minimize,
        // need to evaluate for the last playing side with the right value.
        if (depth == 0)
            return evaluate(board, !maximize);

        int bestscore;

        if (maximize)
            bestscore = std::numeric_limits<int>::min();
        else
            bestscore = std::numeric_limits<int>::max();

        const std::vector<Move> moves = board.generate_legal_moves();

        for (Move move: moves)
        {
            Chessboard new_board = Chessboard(board);
            new_board.do_move(move);

            int score = minimax_(new_board, depth - 1, alpha, beta, !maximize);

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
                break;
        }

        return bestscore;
    }

    Move Search::minimax_start_(int depth)
    {
        int bestscore = std::numeric_limits<int>::min();

        int alpha = std::numeric_limits<int>::min();
        int beta = std::numeric_limits<int>::max();

        std::vector<Move> moves = board_.generate_legal_moves();

        Move bestmove = moves.at(0);

        int score;

        for (Move move: moves)
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

        return bestmove;
    }

    Move Search::find_move()
    {
        timeout_ = false;
        start_ = std::chrono::system_clock::now();
        Move current_best;

        for (int deep = 0; ; deep += 1)
        {
            bestmove_ = current_best;
            current_best = minimax_start_(depth_ + deep);

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

} // namespace board
