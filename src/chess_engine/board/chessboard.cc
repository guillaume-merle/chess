#include "chessboard.hh"

namespace board
{
    Chessboard::get_bitboard(BitboardPiece piece)
    {
        return bitboards_[piece];
    }
}
