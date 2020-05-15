#include "evaluation.hh"

namespace board
{
    int evaluate(Chessboard& board)
    {
        int score = 0;

        if (board.is_checkmate(board.current_color()))
            score += 10000;
        else if (board.is_check(board.current_color()))
            score += 5000;

        score += (8 - popcount(board.get(board.current_color(), QUEEN))) * 300;
        score += (8 - popcount(board.get(board.current_color(), KNIGHT))) * 200;
        score += (8 - popcount(board.get(board.current_color(), BISHOP))) * 50;
        score += (8 - popcount(board.get(board.current_color(), ROOK))) * 50;
        score += (8 - popcount(board.get(board.current_color(), PAWN))) * 10;

        if (board.current_color() == BLACK)
        {
            if (board.is_checkmate(WHITE))
                score -= 500;
            else if (board.is_check(WHITE))
                score -= 250;

            score += (popcount(board.get(WHITE, QUEEN))) * 300;
            score += (popcount(board.get(WHITE, KNIGHT))) * 200;
            score += (popcount(board.get(WHITE, BISHOP))) * 50;
            score += (popcount(board.get(WHITE, ROOK))) * 50;
            score += (popcount(board.get(WHITE, PAWN))) * 10;
        }
        else
        {
            if (board.is_checkmate(BLACK))
                score -= 500;
            else if (board.is_check(BLACK))
                score -= 250;
            score += (popcount(board.get(BLACK, QUEEN))) * 300;
            score += (popcount(board.get(BLACK, KNIGHT))) * 200;
            score += (popcount(board.get(BLACK, BISHOP))) * 50;
            score += (popcount(board.get(BLACK, ROOK))) * 50;
            score += (popcount(board.get(BLACK, PAWN))) * 10;
        }

        return score;
    }

} // namespace board
