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

    Bitboard Move::get_from()
    {
        return from_;
    }

    Bitboard Move::get_to()
    {
        return to_;
    }

    void add_move(std::vector<Move>& moves, Bitboard from, Bitboard to,
                  PieceType piece)
    {
        if (to)
            moves.emplace_back(Move(from, to, piece));
    }
}
