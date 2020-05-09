#include <iostream>

#include "chessboard.hh"
#include "rule.hh"
#include "utils.hh"
#include "move.hh"

namespace board
{
    Bitboard Chessboard::get(BitboardType piece)
    {
        return bitboards_[piece];
    }

    Bitboard Chessboard::get(int piece)
    {
        return bitboards_[piece];
    }

    bool Chessboard::is_white_turn()
    {
        return white_turn_;
    }

    bool Chessboard::set(BitboardType piece, Bitboard value)
    {
        if (piece < 0 || piece >= BITBOARDS_NUMBER)
            return false;

        bitboards_[piece] = value;
        return true;
    }

    Chessboard::opt_piece_t
    Chessboard::operator[](const Position&) const
    {
        return std::nullopt;
    }

    bool Chessboard::would_collide(Bitboard pos, Color color)
    {
        if (color == Color::WHITE
                && (pos & get(BitboardType::ALLWHITE)))
            return true;

        if (color == Color::BLACK
                && (pos & get(BitboardType::ALLBLACK)))
            return true;

        return false;
    }

    bool Chessboard::would_capture(Bitboard pos, Color color)
    {
        if (color == Color::WHITE
                && (pos & get(BitboardType::ALLBLACK)))
            return true;

        if (color == Color::BLACK
                && (pos & get(BitboardType::ALLWHITE)))
            return true;

        return false;
    }

    bool Chessboard::is_check()
    {
        std::vector<Move> moves;
        moves += generate_pawn_moves(*this);
        moves += generate_king_moves(*this);
        moves += generate_bishop_moves(*this);
        moves += generate_rook_moves(*this);
        moves += generate_queen_moves(*this);
        moves += generate_knight_moves(*this);

        for (auto& move : moves)
        {
            if (move.is_capture() && move.get_capture() == PieceType::KING)
                return true;
        }

        return false;
    }
}
