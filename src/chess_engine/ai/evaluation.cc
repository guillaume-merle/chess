#include "evaluation.hh"

namespace board
{
    int evaluate(Chessboard& board)
    {
        int score = 0;

        Color opposent_color = board.current_color();
        Color color;

        if (opposent_color == BLACK)
            color = WHITE;
        else
            color = BLACK;

        if (board.is_checkmate(opposent_color))
            score += 900;
        else if (board.is_check(opposent_color))
            score += 30;

        score += (3 - popcount(board.get(opposent_color, QUEEN))) * 90;
        score += (2 - popcount(board.get(opposent_color, KNIGHT))) * 40;
        score += (2 - popcount(board.get(opposent_color, BISHOP))) * 30;
        score += (2 - popcount(board.get(opposent_color, ROOK))) * 50;
        score += (8 - popcount(board.get(opposent_color, PAWN))) * 10;

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
