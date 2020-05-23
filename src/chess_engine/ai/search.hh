#pragma once

#include <chrono>
#include <map>
#include <cstdint>
#include <iterator>

#include "chessboard.hh"
#include "move-heuristics.hh"
#include "ttable.hh"

using namespace board;

namespace ai
{
    const int INF = std::numeric_limits<int>::max();

    using time_point = std::chrono::time_point<std::chrono::system_clock>;
    /**
     * @brief class representing the search of moves.
     *
     */
    class Search
    {
    public:
        /**
         * @brief Construct a new Search object.
         *
         */
        Search();

        /**
         * @brief function which returns the best move to play.
         */
        Move search_move();

        Chessboard& get_board();

        Move& get_bestmove();

        Color our_color();

        int negamax_(Chessboard& board, int depth, int alpha, int beta);

        Move negamax_start_(int depth);

        int quiesce_(Chessboard& board, int alpha, int beta);

        Move find_move();

        /**
         * @brief Initialize a new search by reseting some attributes.
         */
        void new_search();

        /**
         * @brief add the board disposition to the map board_dispositions_
         */
        std::map<uint64_t, int>::iterator
        add_board_disposition(uint64_t zobrist_key);

        /**
         * @brief Check if there is ALREADY a threefold repetition
         * for the given Chessboard.
         *
         * @param board the chessboard to check for.
         * @return true if there is a repetition.
         */
        bool threefold_repetition(Chessboard& board);

    private:
        const int base_depth_ = 2;

        int deep_depth_ = 0;

        Chessboard board_;

        Color us_;

        Move bestmove_;

        int bestscore_;

        bool timeout_;

        time_point start_;

        std::chrono::seconds time_;

        /**
         * @brief Transposition Table.
         */
        TTable ttable_;

        MoveHeuristics heuristics_;

        std::map<uint64_t, int> board_dispositions_;
    };

} // namespace board
