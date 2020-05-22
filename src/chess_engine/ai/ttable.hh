#pragma once

#include <unordered_map>
#include <memory>

#include "ttable-entry.hh"

namespace ai
{
    /**
     * @brief Class representing a Transposition Table.
     *
     */
    class TTable
    {
    public:
        /**
         * @brief Construct a new Transposition Table.
         */
        TTable() = default;

        /**
         * @brief Insert a new Entry in the table.
         *
         * @param key the zobrist_key.
         * @param depth.
         * @param score of the search.
         * @param flag the type of the search.
         * @param bestmove the bestmove of the search if there is one.
         * @return true if the entry was inserted.
         */
        void insert(uint64_t key, int depth, int score,
                    TTableEntryFlag flag, Move& bestmove);

        /**
         * @brief Get the TTableEntry for the given key.
         *
         * @param key the zobrist_key.
         * @param depth the minimum depth that the entry has to match.
         * @return an optional to a TTableEntry.
         */
        std::shared_ptr<TTableEntry> at(uint64_t key, int depth = -1);

        /**
         * @brief Clear the transposition table.
         */
        void clear();

    private:
        /**
         * @brief Hashmap representing the transposition table.
         * It contains pairs of hashkey and TTableEntry.
         * (hashkey = zobrist_key % table size)
         */
        std::unordered_map<uint64_t, std::shared_ptr<TTableEntry>> map_;
    };

} // namespace ai
