#include "king.hh"

namespace board
{
    std::vector<Move>
    King::generate_moves(std::vector<Move>& moves, Bitboard bitboard)
    {
        Bitboard generated = north(bitboard, 1);
        if (generated)
            moves.emplace_back(Move(bitboard, generated, PieceType::KING));

        generated = south(bitboard, 1);
        if (generated)
            moves.emplace_back(Move(bitboard, generated, PieceType::KING));

        // the king is not on the left side
        if ((left_side & bitboard) != 0)
        {
            generated = west(bitboard, 1);
            if (generated)
                moves.emplace_back(Move(bitboard, generated, PieceType::KING));

            generated = northwest(bitboard, 1);
            if (generated)
                moves.emplace_back(Move(bitboard, generated, PieceType::KING));

            generated = southwest(bitboard, 1);
            if (generated)
                moves.emplace_back(Move(bitboard, generated, PieceType::KING));
        }

        // the king is not on the right side
        if ((right_side & bitboard) != 0)
        {
            generated = east(bitboard, 1);
            if (generated)
                moves.emplace_back(Move(bitboard, generated, PieceType::KING));

            generated = northeast(bitboard, 1);
            if (generated)
                moves.emplace_back(Move(bitboard, generated, PieceType::KING));

            generated = southeast(bitboard, 1);
            if (generated)
                moves.emplace_back(Move(bitboard, generated, PieceType::KING));
        }

        return moves;
    }
}
