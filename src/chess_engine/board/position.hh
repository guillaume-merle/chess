#pragma once

#include <utility>

#include "utype.hh"
#include "bitboard.hh"

namespace board
{
    /* The file enum represent the colomns
     * on the board */
    enum File
    {
        A = 0,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
    };

    /* The rank enum represent the lines
     * on the board */
    enum Rank
    {
        ONE = 0,
        TWO,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
    };


    /* Position represent a coordinate on the board */
    class Position final
    {
    public:
        Position() = default;

        Position(File file, Rank rank);

        File file_get() const;
        Rank rank_get() const;

        bool operator==(const Position& pos) const;

        bool operator!=(const Position& pos) const;

        Square to_square() const;

    private:
        File file_;
        Rank rank_;
    };

} // namespace board

#include "position.hxx"
