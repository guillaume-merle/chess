#pragma once

#include <string>
#include <vector>

#include "fen-object.hh"

namespace board
{
    class PerftObject
    {
    public:
        
        PerftObject() = default;

        FenObject fen_get();

        int depth_get();

    private:
    
        FenObject fen_;
        int depth_;
    };
} // namespace perft_parser
