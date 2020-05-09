#include "perft-object.hh"

namespace board
{
    FenObject PerftObject::fen_get()
    {
        return fen_;
    }

    int PerftObject::depth_get()
    {
        return depth_;
    }
} // namespace board
