#include <iostream>

#include "chessboard.hh"
#include "rule.hh"
#include "utils.hh"
#include "move.hh"

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

    bool Chessboard::is_check()
    {
        std::vector<Move> moves;
        // moves += generate_pawn_moves(*this);
        // moves += generate_king_moves(*this);
        // moves += generate_bishop_moves(*this);
        // moves += generate_rook_moves(*this);
        // moves += generate_queen_moves(*this);
        // moves += generate_knight_moves(*this);

        for (auto& move : moves)
        {
            if (move.is_capture() && move.get_capture() == PieceType::KING)
                return true;
        }

        return false;
    }
}
