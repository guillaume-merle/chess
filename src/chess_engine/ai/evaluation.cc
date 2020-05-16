#include "evaluation.hh"

namespace ai
{
    int evaluate(Chessboard& board, bool maximize)
    {
        int score = 0;

        Color color;
        Color other_color;

        // maximize last color to play
        if (maximize)
        {
            other_color = board.current_color();
            color = opposite_color(other_color);
        }
        // minimize last color to play
        else
        {
            color = board.current_color();
            other_color = opposite_color(color);
        }

        if (board.is_checkmate(other_color))
            score += 900;
        else if (board.is_check(other_color))
            score += 30;

        score += (3 - popcount(board.get(other_color, QUEEN))) * 90;
        score += (2 - popcount(board.get(other_color, KNIGHT))) * 40;
        score += (2 - popcount(board.get(other_color, BISHOP))) * 30;
        score += (2 - popcount(board.get(other_color, ROOK))) * 50;
        score += (8 - popcount(board.get(other_color, PAWN))) * 10;

        if (board.is_checkmate(color))
            score -= 900;
        else if (board.is_check(color))
            score -= 100;

        score += (popcount(board.get(color, QUEEN))) * 450;
        score += (popcount(board.get(color, KNIGHT))) * 50;
        score += (popcount(board.get(color, BISHOP))) * 50;
        score += (popcount(board.get(color, ROOK))) * 70;
        score += (popcount(board.get(color, PAWN))) * 15;

        return score;
    }

} // namespace board
