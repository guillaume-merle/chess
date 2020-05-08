#include "chessboard.hh"

namespace board
{
    Bitboard Chessboard::get(BitboardType piece)
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
}
