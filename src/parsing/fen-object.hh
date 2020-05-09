#pragma once

#include <string>
#include <vector>

#include "fen-rank.hh"
#include "color.hh"
#include "position.hh"
#include "piece-type.hh"

namespace board
{
    class FenObject
    {
    public:
        FenObject() = default;

        //operator[] TODO
        
        Color side_to_move_get();

        std::vector<char> castling_get();

        Position en_passant_target_get();

    private:
        
        std::vector<FenRank> ranks_;
        Color side_to_move_;
        std::vector<char> castling_;
        Position en_passant_target_;
    };
} // namespace perft_parser
