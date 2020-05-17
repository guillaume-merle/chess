#pragma once

#include <chrono>

#include "chessboard.hh"
#include "move.hh"

using namespace board;

namespace ai
{
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

        int minimax_(Chessboard& board, int depth, int alpha, int bet,
                     bool maximize);

        Move minimax_start_(int depth);

        int quiesce_(Chessboard& board, int alpha, int beta, bool maximize);

        Move find_move();

    private:
        const int depth_ = 2;

        Chessboard board_;

        Color us_;

        Move bestmove_;

        bool timeout_;

        time_point start_;

        std::chrono::seconds time_;
    };

} // namespace board
