#include "rook.hh"

namespace board
{
    std::vector<Move>
    Rook::generate_moves(std::vector<Move>& moves, Bitboard bitboard)
    {
        Chessboard board;
        return generate_moves(moves, bitboard, board);
    }

    std::vector<Move>
    Rook::generate_moves(std::vector<Move>& moves, Bitboard bitboard,
            Chessboard& board, Color color)
    {
        PieceType piece = PieceType::ROOK;

        Bitboard pos = north(bitboard);
        while (add_move(moves, bitboard, pos, piece, color, board))
        {
            pos = north(pos);
        }

        pos = south(bitboard);
        while (add_move(moves, bitboard, pos, piece, color, board))
        {
            pos = south(pos);
        }

        pos = east(bitboard);
        while (add_move(moves, bitboard, pos, piece, color, board))
        {
            pos = east(pos);
        }

        pos = west(bitboard);
        while (add_move(moves, bitboard, pos, piece, color, board))
        {
            pos = west(pos);
        }

        return moves;
    }
}
