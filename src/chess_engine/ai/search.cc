#include <limits>
#include <algorithm>

#include "evaluation.hh"
#include "search.hh"

namespace ai
{
    Search::Search()
        : board_(), us_(board_.current_color()), depth_(4)
    {}

    Chessboard& Search::get_board()
    {
        return board_;
    }

    int Search::minimax_(Chessboard& board, int depth, int alpha, int beta,
                         bool maximize)
    {
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

    Move Search::search_move()
    {
        int bestscore = std::numeric_limits<int>::min();

        int alpha = std::numeric_limits<int>::min();
        int beta = std::numeric_limits<int>::max();

        std::vector<Move> moves = board_.generate_legal_moves();

        Move bestmove = moves[0];

        int score;

        for (Move move: moves)
        {
            Chessboard new_board = board_;
            new_board.do_move(move);

            score = minimax_(new_board, depth_ - 1, alpha, beta, false);
            if (score > bestscore)
            {
                bestscore = score;
                bestmove = move;
            }

            alpha = std::max(alpha, bestscore);
        }

        return bestmove;
    }
} // namespace board
