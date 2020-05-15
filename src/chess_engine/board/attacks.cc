#include "attacks.hh"
#include "knight.hh"

namespace board
{
    board::Attacks attacks_g;

    Attacks::Attacks()
    {
        init_knight_attacks();
        init_king_attacks();
        init_pawn_attacks();
    }

    Bitboard Attacks::get_bishop_attacks(const Square square,
                                         const Bitboard occupancy) const
    {
        return magic_.get_bishop_moves(square, occupancy);
    }

    Bitboard Attacks::get_rook_attacks(const Square square,
                                       const Bitboard occupancy) const
    {
        return magic_.get_rook_moves(square, occupancy);
    }

    Bitboard Attacks::get_queen_attacks(const Square square,
                                        const Bitboard occupancy) const
    {
        return get_bishop_attacks(square, occupancy)
               | get_rook_attacks(square, occupancy);
    }

    Bitboard Attacks::get_knight_attacks(const Square square) const
    {
        return knight_attacks_[square];
    }

    Bitboard Attacks::get_king_attacks(const Square square) const
    {
        return king_attacks_[square];
    }

    Bitboard
    Attacks::get_pawn_attacks(const Square square, Color color) const
    {
        return pawn_attacks_[color][square];
    }

    void Attacks::init_knight_attacks()
    {
        for (int i = 0; i < 64; i++)
        {
            Bitboard pos = 1ULL << i;
            Bitboard attacks =
                northwestwest(pos) | northeasteast(pos)
                | southwestwest(pos) | southeasteast(pos)
                | northnorthwest(pos) | northnortheast(pos)
                | southsouthwest(pos) | southsoutheast(pos);

            knight_attacks_[i] = attacks;
        }
    }

    void Attacks::init_king_attacks()
    {
        for (int i = 0; i < 64; i++)
        {
            Bitboard pos = 1ULL << i;
            Bitboard attacks =
                north(pos) | northeast(pos) | east(pos) | southeast(pos)
                | south(pos) | southwest(pos) | west(pos) | northwest(pos);

            king_attacks_[i] = attacks;
        }
    }

    void Attacks::init_pawn_attacks()
    {
        for (int i = 0; i < 64; i++)
        {
            Bitboard pos = 1ULL << i;
            Bitboard white_attacks = northwest(pos) | northeast(pos);
            Bitboard black_attacks = southwest(pos) | southeast(pos);

            pawn_attacks_[WHITE][i] = white_attacks;
            pawn_attacks_[BLACK][i] = black_attacks;
        }
    }
}
