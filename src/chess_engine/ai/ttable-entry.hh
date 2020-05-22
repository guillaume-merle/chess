#pragma once

#include "move.hh"

using namespace board;

namespace ai
{
    /**
     * @brief Enum representing the state of an entry.
     */
    enum TTableEntryFlag
    {
        EXACT = 0, // Exact score
        ALPHA, // Score lower than alpha
        BETA, // score greater than beta
    };

    /**
     * @brief Class representing a transposition table entry.
     *
     */
    class TTableEntry
    {
    public:
        /**
         * @brief Construc a new Transposition Table Entry.
         */
        TTableEntry(uint64_t key, int depth, int score, TTableEntryFlag flag,
                    Move& bestmove);

    private:
        /**
         * @brief The zobrist key representing a position of a Chessboard.
         */
        uint64_t key_;

        /**
         * @brief Depth of the search of the entry.
         */
        int depth_;

        /**
         * @brief Score of the search.
         */
        int score_;

        /**
         * @brief Flag representing the search.
         */
        TTableEntryFlag flag_;

        /**
         * @brief Best move of the search.
         */
        Move bestmove_;
    };

} // namespace ai

