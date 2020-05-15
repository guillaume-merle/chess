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

        FenRank(std::string rank);

        side_piece_t operator[](int file);

        size_t size();

    private:
        std::vector<std::pair<PieceType, Color>> pieces_;
    };
} // namespace board
