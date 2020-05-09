#pragma once

#include <string>
#include <vector>

#include "color.hh"
#include "piece-type.hh"

namespace board
{
    class FenRank
    {
    public:

        using side_piece_t = std::pair<PieceType, Color>;
        using piece_t = std::vector<side_piece_t>;
        
        FenRank() = default;

        //operator[] TODO

    private:

        piece_t pieces_;
    };
} // namespace perft_parser
