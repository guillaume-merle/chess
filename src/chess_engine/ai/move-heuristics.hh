#pragma once

#include "move.hh"

using namespace board;

namespace ai
{
    /**
     * Class conaining heuristics for the move ordering:
     * * history
     * * killer move
     *
     */
    class MoveHeuristics
    {
    public:
        /**
         * @brief Construct a new MoveHeuristics object.
         */
        MoveHeuristics();

        /**
         * @brief Get the killer move for the given depth.
         *
         * @param depth.
         * @return The killer move.
         */
        Move get_killer(int depth) const;

        /**
         * @brief Set the killer move for the given depth.
         *
         * @param move the move to insert.
         * @param depth the corresponding depth.
         */
        void set_killer(Move move, int depth);

    private:
        /**
         * @brief Maximum killer move depth.
         */
        static const int killers_depth_ = 30;

        /**
         * @brief History heuristic stocking score for [Color][from][to],
         * from and to beeing squares.
         */
        int history_[2][64][64];

        /**
         * @brief A dynamic, path-dependent move ordering technique.
         * Stores the best move for a depth.
         */
        Move killer_[killers_depth_];

    };

} // namespace ai
