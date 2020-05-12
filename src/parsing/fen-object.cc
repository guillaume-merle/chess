#include "fen-object.hh"

namespace board
{
    //FenObject(); //TODO

    //operator[] TODO

    Color FenObject::side_to_move_get()
    {
        return side_to_move_;
    }

    std::vector<char> FenObject::castling_get()
    {
        return castling_;
    }

    Position FenObject::en_passant_target_get()
    {
        return en_passant_target_;
    }
} // namespace board
