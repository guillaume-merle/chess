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

        /**
         * @brief Compute the time needed for the next search
         * based on the current turn and other variables.
         * It sets the attribute time_.
         *
         * @param turn the current turn of the game.
         */
        void compute_time();

    private:
        const int base_depth_ = 2;

        int deep_depth_ = 0;

        Chessboard board_;

        Color us_;

        Move bestmove_;

        int bestscore_;

        bool timeout_;

        /**
         * @brief Time point representing the start of the current search.
         */
        time_point start_;

        /**
         * @brief The time allocated for the current search.
         */
        std::chrono::milliseconds time_;

        /**
         * @brief Represent the total used time since the begining of the game
         * (Made for a Blitz of 5 minutes = 300 seconds)
         */
        std::chrono::milliseconds total_elapsed_time_{300000};

        /**
         * @brief Transposition Table.
         */
        TTable ttable_;

        /**
         * @brief Move heuristics for the current search.
         * Used in Move Ordering.
         */
        MoveHeuristics heuristics_;

        /**
         * @brief map of previous board dispositions in the game.
         * Used to detect threefold repetition draws.
         */
        std::map<uint64_t, int> board_dispositions_;
    };

} // namespace board
