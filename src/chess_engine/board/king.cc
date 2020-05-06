#include "king.hh"

namespace board
{
    std::vector<Move>
    King::generate_moves(std::vector<Move>& moves, Bitboard bitboard)
    {
        add_move(moves, bitboard, north(bitboard, 1), PieceType::KING);

        add_move(moves, bitboard, south(bitboard, 1), PieceType::KING);

        // check if the king is not on the left side
        if ((left_side & bitboard) != 0)
        {
            add_move(moves, bitboard, west(bitboard, 1), PieceType::KING);

            add_move(moves, bitboard, northwest(bitboard, 1), PieceType::KING);

            add_move(moves, bitboard, southwest(bitboard, 1), PieceType::KING);
        }

        // icheck if the king is not on the right side
        if ((right_side & bitboard) != 0)
        {
            add_move(moves, bitboard, east(bitboard, 1), PieceType::KING);

            add_move(moves, bitboard, northeast(bitboard, 1), PieceType::KING);

            add_move(moves, bitboard, southeast(bitboard, 1), PieceType::KING);
        }

        return moves;
    }
}
