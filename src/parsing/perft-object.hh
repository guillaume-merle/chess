#pragma once

#include <string>
#include <vector>

#include "fen-object.hh"

namespace board
{
    class PerftObject
    {
    public:
        
        PerftObject(FenObject fen, int depth)
            : fen_(fen), depth_(depth)
        {};

        FenObject fen_get();

        int depth_get();

    private:
    
        FenObject fen_;
        int depth_;
    };
} // namespace board
