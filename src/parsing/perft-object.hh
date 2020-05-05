#pragma once

#include <string>
#include <vector>

#include "fen-object.hh"

namespace perft_parser
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
