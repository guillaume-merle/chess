#include <iostream>

#include "perft.hh"
#include "movegen.hh"

namespace board
{
    unsigned long long _perft(Chessboard board, int depth)
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

    void perft(PerftObject& perft_obj)
    {
        Chessboard board;
        board.set_from_fen(perft_obj.fen_get());

        size_t leaves = _perft(board, perft_obj.depth_get());
        std::cout << leaves << "\n";
    }

    void divide(PerftObject& perft_obj)
    {
        Chessboard board;
        board.set_from_fen(perft_obj.fen_get());

        std::vector<Move> moves = board.generate_legal_moves();
        size_t nodes = 0;

        for (auto& move : moves)
        {
            Chessboard temp_board = board;
            temp_board.do_move(move);

            unsigned long long res = _perft(temp_board,
                                            perft_obj.depth_get() - 1);
            nodes += res;

            std::cout << move.to_string() << ": " << res  << "\n";
        }

        std::cout << "\n====================\n";
        std::cout << "Leaves: " << nodes << "\n";
    }
}
