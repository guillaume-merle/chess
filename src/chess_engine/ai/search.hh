#pragma once

#include "chessboard.hh"
#include "move.hh"

using namespace board;

namespace ai
{
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

        Color our_color();

        int minimax_(Chessboard& board, int depth, bool maximize);

    private:
        Chessboard board_;

        Color us_;

        int depth_;
    };

} // namespace board
