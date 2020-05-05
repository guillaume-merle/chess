#include "chessboard.hh"

namespace board
{
    Bitboard Chessboard::get_bitboard(BitboardPiece piece)
    {
        return bitboards_[piece];
    }

    bool Chessboard::is_white_turn()
    {
        return white_turn_;
    }

    Chessboard::opt_piece_t
    Chessboard::operator[](const Position&) const
    {
        return std::nullopt;
    }
}
