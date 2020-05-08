#include "chessboard.hh"

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
}
