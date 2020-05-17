#include "evaluation.hh"
#include "bitboard.hh"

namespace ai
{
    int get_position_score(const int bonus_matrix[8][8], Square square,
                           Color color)
    {
        if (color == BLACK)
            square = 63 - square;

        int x = 7 - (square % 8);

        int y = square / 8;

        return bonus_matrix[x][y];
    }

    int get_position_bonus(Chessboard& board, Color color)
    {
        int score = 0;
        Bitboard pawns = board.get(color, PAWN);
        Bitboard knights = board.get(color, KNIGHT);
        Bitboard bishops = board.get(color, BISHOP);
        Bitboard rooks = board.get(color, ROOK);
        Bitboard queen = board.get(color, QUEEN);
        Bitboard king = board.get(color, KING);

        Square square;
        while (pawns)
        {
            square = pop(pawns);
            score +=
                get_position_score(pawns_mobility_bonus, square, color);
        }

        while (knights)
        {
            square = pop(knights);
            score +=
                get_position_score(knights_mobility_bonus, square, color);
        }

        while (bishops)
        {
            square = pop(bishops);
            score +=
                get_position_score(bishops_mobility_bonus, square, color);
        }

        while (rooks)
        {
            square = pop(rooks);
            score +=
                get_position_score(rooks_mobility_bonus, square, color);
        }

        while (queen)
        {
            square = pop(queen);
            score +=
                get_position_score(queen_mobility_bonus, square, color);
        }

        while (king)
        {
            square = pop(king);
            score +=
                get_position_score(king_mobility_bonus, square, color);
        }

        return score;
    }

    int evaluate(Chessboard& board, bool maximize)
    {
        int score = get_position_bonus(board, board.current_color());

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
            score += 20000;
        else if (board.is_check(other_color))
            score += 60;

        score += (3 - popcount(board.get(other_color, QUEEN))) * 900;
        score += (2 - popcount(board.get(other_color, KNIGHT))) * 320;
        score += (2 - popcount(board.get(other_color, BISHOP))) * 330;
        score += (2 - popcount(board.get(other_color, ROOK))) * 500;
        score += (8 - popcount(board.get(other_color, PAWN))) * 100;

        if (board.is_checkmate(color))
            score -= 20000;
        else if (board.is_check(color))
            score -= 500;

        score += (popcount(board.get(color, QUEEN))) * 5000;
        score += (popcount(board.get(color, KNIGHT))) * 400;
        score += (popcount(board.get(color, BISHOP))) * 450;
        score += (popcount(board.get(color, ROOK))) * 700;
        score += (popcount(board.get(color, PAWN))) * 110;

        score += get_position_bonus(board, color);

        score -= get_position_bonus(board, other_color);

        return score;
    }

} // namespace board
