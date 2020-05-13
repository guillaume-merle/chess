#include <iostream>

#include "perft.hh"
#include "movegen.hh"

namespace board
{
    size_t _perft(Chessboard board, int depth)
    {
        if (depth == 0)
            return 1;

        std::vector<Move> moves = board.generate_legal_moves();
        size_t nodes = 0;

        for (auto& move : moves)
        {
            Chessboard temp_board = board;
            temp_board.do_move(move);

            nodes += _perft(temp_board, depth - 1);
        }

        return nodes;
    }

    size_t perft(PerftObject& perft_obj)
    {
        Chessboard board;
        board.set_from_fen(perft_obj.fen_get());

        size_t leaves = _perft(board, perft_obj.depth_get());
        std::cout << leaves << "\n";

        return leaves;
    }
}
