#pragma once

#include <string>
#include <vector>

#include "fen-rank.hh"
#include "position.hh"

namespace board
{
    class FenObject
    {
    public:

        FenObject(std::vector<FenRank> ranks, Color side_to_move,
                  std::vector<char> castling, Position en_passant_target)
            : ranks_(ranks), side_to_move_(side_to_move),
              castling_(castling), en_passant_target_(en_passant_target)
        {};

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
} // namespace board
