#include "attacks.hh"
#include "knight.hh"
#include "color.hh"

namespace board
{
    Bitboard attacks::_knight_attacks[64] = {0};
    Bitboard attacks::_king_attacks[64] = {0};
    Bitboard attacks::_pawn_attacks[2][64] = {{0}};

    void attacks::init()
    {
        magic::init();
        attacks::init_knight_attacks();
        attacks::init_king_attacks();
        attacks::init_pawn_attacks();
    }

    Bitboard attacks::get_bishop_attacks(const unsigned int square,
            const Bitboard occupancy)
    {
        return *(magic::magicmoves_b_indices[square] +
                (((occupancy & magic::magicmoves_b_mask[square])
                  * magic::magicmoves_b_magics[square])
                 >> magic::magicmoves_b_shift[square]));
    }

    Bitboard attacks::get_rook_attacks(const unsigned int square,
            const Bitboard occupancy)
    {
        return *(magic::magicmoves_r_indices[square] +
                (((occupancy & magic::magicmoves_r_mask[square])
                  * magic::magicmoves_r_magics[square])
                 >> magic::magicmoves_r_shift[square]));
    }

    Bitboard attacks::get_queen_attacks(const unsigned int square,
            const Bitboard occupancy)
    {
        return get_bishop_attacks(square, occupancy)
            | get_rook_attacks(square, occupancy);
    }

    Bitboard attacks::get_knight_attacks(const unsigned int square)
    {
        return _knight_attacks[square];
    }

    Bitboard attacks::get_king_attacks(const unsigned int square)
    {
        return _king_attacks[square];
    }

    Bitboard attacks::get_pawn_attacks(const unsigned int square, Color color)
    {
        return _pawn_attacks[color][square];
    }

    void attacks::init_knight_attacks()
    {
        for (int i = 0; i < 64; i++)
        {
            Bitboard pos = 1 << i;
            Bitboard attacks =
                Knight::northwestwest(pos) | Knight::northeasteast(pos)
                | Knight::southwestwest(pos) | Knight::southeasteast(pos)
                | Knight::northnorthwest(pos) | Knight::northnortheast(pos)
                | Knight::southsouthwest(pos) | Knight::southsoutheast(pos);

            _knight_attacks[i] = attacks;
        }
    }

    void attacks::init_king_attacks()
    {
        for (int i = 0; i < 64; i++)
        {
            Bitboard pos = 1 << i;
            Bitboard attacks =
                north(pos) | northeast(pos) | east(pos) | southeast(pos)
                | south(pos) | southwest(pos) | west(pos) | northwest(pos);

            _king_attacks[i] = attacks;
        }
    }

    void attacks::init_pawn_attacks()
    {
        for (int i = 0; i < 64; i++)
        {
            Bitboard pos = 1 << i;
            Bitboard white_attacks = northwest(pos) | northeast(pos);
            Bitboard black_attacks = southwest(pos) | southeast(pos);

            _pawn_attacks[WHITE][i] = white_attacks;
            _pawn_attacks[BLACK][i] = black_attacks;
        }
    }
}
