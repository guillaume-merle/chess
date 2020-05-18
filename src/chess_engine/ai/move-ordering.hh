#pragma once

#include "move-heuristics.hh"

using namespace board;

namespace ai
{
    enum Grade
    {
        KILLER = 2000,
        PROMOTION = 3000,
        CAPTURE = 4000,
    };

    /**
     * @brief class representing the ordering of a list of moves.
     *
     */
    class MoveOrdering
    {
    public:
        /**
         * @brief Construct a MoveOrdering from a list of moves
         *
         * @param moves the list of moves.
         */
        MoveOrdering(std::vector<Move>& moves, MoveHeuristics& heuristics,
                     int depth = 0);

        /**
         * @brief Get the ordered moves.
         *
         * @return The vector of ordered moves.
         */
        std::vector<Move>& get();

        /**
         * @brief Grade the moves on various criterias:
         * * MVV-LVA
         * * Promotion and promoted piece value
         * *...
         */
        void grade_moves_();

        /**
         * @brief Sort the moves from their score.
         */
        void order_moves_();

        /**
         * @brief Initialize static variables.
         */
        static void init();

    private:
        /**
         * @brief Vector of moves.
         */
        std::vector<Move>& moves_;

        /**
         * @brief Move heuristics for the current search.
         */
        MoveHeuristics& heuristics_;

        /**
         * @brief Real current depth (or ply).
         */
        int depth_;

        /**
         * @brief Array containing the values of the MVV-LVA
         * (Most Valuable Victim - Least Valuable Aggressor)
         * for the different pieces as aggressors and vitims.
         */
        static int mvv_lva_[5][6];
    };
}
