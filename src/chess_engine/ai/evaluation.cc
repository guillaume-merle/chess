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

    int get_material_score(PieceType piece, bool endgame)
    {
        if (piece == PAWN)
            return endgame ? 140 : 100;

        if (piece == KNIGHT)
            return endgame ? 320 : 300;

        if (piece == BISHOP)
            return endgame ? 330 : 300;

        if (piece == ROOK)
            return endgame ? 500 : 500;

        if (piece == QUEEN)
            return endgame ? 900 : 900;

        return 0;
    }

    int get_position_bonus(Chessboard& board, Color color, bool endgame)
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
            if (endgame)
            {
                score += get_position_score(king_mobility_endgame_bonus,
                                            square, color);
            }
            else
            {
                score +=
                    get_position_score(king_mobility_bonus, square, color);
            }
        }

        return score;
    }

    int evaluate(Chessboard& board, bool maximize)
    {
        int score = 0;

        bool endgame = false;

        if (popcount(board.get(BLACK, ALL) | board.get(WHITE, ALL)) < 10)
            endgame = true;

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

        // Opposent part
        if (board.is_checkmate(other_color))
            score += 32767;
        else if (board.is_check(other_color))
            score += 60;

        score -= popcount(board.get(other_color, QUEEN))
                 * get_material_score(QUEEN, endgame);

        score -= popcount(board.get(other_color, KNIGHT))
                 * get_material_score(KNIGHT, endgame);

        score -= popcount(board.get(other_color, BISHOP))
                 * get_material_score(BISHOP, endgame);

        score -= popcount(board.get(other_color, ROOK))
                 * get_material_score(ROOK, endgame);

        score -= popcount(board.get(other_color, PAWN))
                 * get_material_score(PAWN, endgame);

        // Current color part
        if (board.is_checkmate(color))
            score -= 32767;
        else if (board.is_check(color))
            score -= 100;

        score += (popcount(board.get(color, QUEEN)))
                * (get_material_score(QUEEN, endgame) + 4100);

        score += (popcount(board.get(color, KNIGHT)))
                * (get_material_score(KNIGHT, endgame) + 80);

        score += (popcount(board.get(color, BISHOP)))
                * (get_material_score(BISHOP, endgame) + 120);

        score += (popcount(board.get(color, ROOK)))
                * (get_material_score(ROOK, endgame) + 200);

        score += (popcount(board.get(color, PAWN)))
                * (get_material_score(PAWN, endgame) + 10);


        // Bonus from position
        score += get_position_bonus(board, color, endgame);

        score -= get_position_bonus(board, other_color, endgame);

        return score;
    }

} // namespace board
