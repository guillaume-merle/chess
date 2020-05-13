#include <iostream>

#include "perft.hh"
#include "movegen.hh"

namespace board
{
    size_t _perft(Chessboard board, int depth)
    {
        if (depth == 0)
            return 1;

        std::vector<Move> moves = board::MoveGen(board).get();
        size_t nodes = 0;

        for (auto& move : moves)
        {
            std::cout << "MOVE: " << move.get_from() << " to " << move.get_to() << "\n";

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

        // std::cout << "WHITE:\n";
        // for (int j = 0; j < 7; j++)
        // {
            // std::cout << j << "\n";
            // print_bitboard(board.get(WHITE, j));
        // }
//
        // std::cout << "BLACK:\n";
        // for (int j = 0; j < 7; j++)
        // {
            // std::cout << j << "\n";
            // print_bitboard(board.get(BLACK, j));
        // }

        size_t leaves = _perft(board, perft_obj.depth_get());
        std::cout << leaves << "\n";

        return leaves;
    }
}
