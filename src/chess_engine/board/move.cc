#include "move.hh"

namespace board
{
    Move::Move(Bitboard from, Bitboard to, PieceType piece)
        : from_(from), to_(to), piece_(piece)
    {}

    PieceType Move::piece_get()
    {
        return piece_;
    }
}
