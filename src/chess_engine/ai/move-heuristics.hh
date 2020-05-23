#pragma once

#include "move.hh"
#include "ttable.hh"

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
         * @brief Default constructor.
         */
        MoveHeuristics() = default;

        /**
         * @brief Construct a new MoveHeuristics object.
         *
         * @param ttable the transposition table.
         */
        explicit MoveHeuristics(TTable* ttable);

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

        /**
         * @brief Update the history with the given move.
         *
         * @param color the color to move.
         * @param move.
         * @param depth the depth of the move.
         */
        void set_history(Color color, Move& move, int depth);

        /**
         * @brief Get the history value for the move.
         *
         * @param color the color to play the move.
         * @param move the move to get the value for.
         * @return the stored history value, 0 by default.
         */
        int get_history(Color color, Move& move) const;

        /**
         * @brief Get the transposition table pointer.
         */
        TTable* get_transposition_table();

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

        /**
         * @brief Reference to the transposition table.
         */
        TTable* ttable_ = nullptr;
    };

} // namespace ai
