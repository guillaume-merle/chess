#include "perft.hh"

namespace board
{
    size_t perft(int depth, Chessboard board)
    {
        if (depth == 0)
            return 1;

        std::vector<Move> moves = board.generate_legal_moves();
        size_t nodes = 0;

        for (auto& move : moves)
        {
            Chessboard temp_board = board;
            temp_board.do_move(move);

            nodes += perft(depth - 1, temp_board);
        }

        return nodes;
    }
}
