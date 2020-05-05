#pragma once

#include <string>
#include <vector>

#include "fen-rank.hh"
#include "color.hh"
#include "piece-type.hh"

namespace perft_parser
{
    class FenObject
    {
    public:
        FenObject() = default;

        //operator[] TODO
        
        board::Color side_to_move_get();

        std::vector<char> castling_get();

        board::Position en_passant_target_get();

    private:
        
        std::vector<FenRank> ranks_;
        board::Color side_to_move_;
        std::vector<char> castling_;
        board::Position en_passant_target_;
    };
} // namespace perft_parser
