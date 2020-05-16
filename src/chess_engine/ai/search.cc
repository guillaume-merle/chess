#include <limits>

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

    int Search::minimax_(Chessboard& board, int depth, bool maximize)
    {
        // depth 0 changed the maximize / minimize,
        // need to evaluate for the last playing side with the right value.
        if (depth == 0)
            return evaluate(board, !maximize);

        int value;

        if (maximize)
            value = std::numeric_limits<int>::min();
        else
            value = std::numeric_limits<int>::max();

        const std::vector<Move> moves = board.generate_legal_moves();

        for (Move move: moves)
        {
            Chessboard new_board = Chessboard(board);
            new_board.do_move(move);

            int score = minimax_(new_board, depth - 1, !maximize);

            if (maximize)
            {
                if (score > value)
                    value = score;
            }
            else
            {
                if (score < value)
                    value = score;
            }
        }
        return value;
    }

    Move Search::search_move()
    {
        int bestscore = std::numeric_limits<int>::min();

        std::vector<Move> moves = board_.generate_legal_moves();

        Move best_move = moves[0];

        int score;

        for (Move move: moves)
        {
            Chessboard new_board = board_;
            new_board.do_move(move);

            score = minimax_(new_board, depth_ - 1, false);

            if (score > bestscore)
            {
                bestscore = score;
                best_move = move;
            }
        }
        return best_move;
    }
} // namespace board
