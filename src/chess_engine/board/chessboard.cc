#include <iostream>

#include "chessboard.hh"
#include "rule.hh"
#include "utils.hh"
#include "move.hh"
#include "attacks.hh"

namespace board
{
    Bitboard Chessboard::get(Color color, PieceType piece)
    {
        return bitboards_[color][piece];
    }

    Bitboard Chessboard::get(Color color, int piece)
    {
        return bitboards_[color][piece];
    }

    void Chessboard::update_all_boards()
    {
        Bitboard all_white = 0;
        Bitboard all_black = 0;

        for (int i = 1; i < BITBOARDS_NUMBER; i++)
        {
            all_white |= get(WHITE, i);
            all_black |= get(BLACK, i);
        }

        set(WHITE, ALL, all_white);
        set(BLACK, ALL, all_black);
    }

    PieceType Chessboard::get_piece_type(Square square, Color color)
    {
        Bitboard piece = 1ULL << square;

        for (int i = 1; i < BITBOARDS_NUMBER; i++)
        {
            if (piece & get(color, i))
                return static_cast<PieceType>(i);
        }

        throw std::runtime_error("get_piece_type: the given square doesn't"
                                 "match a piece.");
    }

    bool Chessboard::is_white_turn()
    {
        return white_turn_;
    }

    bool Chessboard::set(Color color, PieceType piece, Bitboard value)
    {
        if (piece < 0 || piece >= BITBOARDS_NUMBER)
            return false;

        bitboards_[color][piece] = value;
        return true;
    }

    Chessboard::opt_piece_t
    Chessboard::operator[](const Position&) const
    {
        return std::nullopt;
    }

    bool Chessboard::would_collide(Bitboard pos, Color color)
    {
        return (pos & get(color, ALL));
    }

    bool Chessboard::would_capture(Bitboard pos, Color color)
    {
        return (pos & get(opposite_color(color), ALL));
    }

    bool Chessboard::is_check(Color color)
    {
        Square king_square = bitscan(get(color, KING));
        Bitboard all_pieces = get(WHITE, ALL) | get(BLACK, ALL);
        Color them = opposite_color(color);

        Bitboard attackers = 0;
        attackers |= attacks::get_knight_attacks(king_square)
                     & get(them, KNIGHT);
        attackers |= attacks::get_pawn_attacks(king_square, color)
                     & get(them, PAWN);
        attackers |= attacks::get_bishop_attacks(king_square, all_pieces)
                     & get(them, BISHOP);
        attackers |= attacks::get_rook_attacks(king_square, all_pieces)
                     & get(them, ROOK);
        attackers |= attacks::get_queen_attacks(king_square, all_pieces)
                     & get(them, QUEEN);

        if (attackers)
            return true;

        return false;
    }
}
