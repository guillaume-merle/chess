#include "evaluation.hh"

namespace board
{
    int evaluate(Chessboard& board)
    {
        int score = 0;

        if (board.is_checkmate(board.current_color()))
            score += 900;
        else if (board.is_check(board.current_color()))
            score += 450;

        score += (4 - popcount(board.get(board.current_color(), QUEEN))) * 90;
        score += (2 - popcount(board.get(board.current_color(), KNIGHT))) * 50;
        score += (2 - popcount(board.get(board.current_color(), BISHOP))) * 30;
        score += (2 - popcount(board.get(board.current_color(), ROOK))) * 50;
        score += (8 - popcount(board.get(board.current_color(), PAWN))) * 5;

        if (board.current_color() == BLACK)
        {
            if (board.is_checkmate(WHITE))
                score -= 900;
            else if (board.is_check(WHITE))
                score -= 250;

            score += (popcount(board.get(WHITE, QUEEN))) * 90;
            score += (popcount(board.get(WHITE, KNIGHT))) * 50;
            score += (popcount(board.get(WHITE, BISHOP))) * 30;
            score += (popcount(board.get(WHITE, ROOK))) * 50;
            score += (popcount(board.get(WHITE, PAWN))) * 10;
        }
        else
        {
            if (board.is_checkmate(BLACK))
                score -= 900;
            else if (board.is_check(BLACK))
                score -= 250;
            score += (popcount(board.get(BLACK, QUEEN))) * 90;
            score += (popcount(board.get(BLACK, KNIGHT))) * 50;
            score += (popcount(board.get(BLACK, BISHOP))) * 30;
            score += (popcount(board.get(BLACK, ROOK))) * 50;
            score += (popcount(board.get(BLACK, PAWN))) * 10;
        }

        return score;
    }

} // namespace board
