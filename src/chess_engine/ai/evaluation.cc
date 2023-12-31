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
            return endgame ? 300 : 320;

        if (piece == BISHOP)
            return endgame ? 300 : 330;

        if (piece == ROOK)
            return endgame ? 500 : 500;

        if (piece == QUEEN)
            return endgame ? 900 : 900;

        return 0;
    }

    int bishop_pair_bonus(Chessboard& board, Color color, bool endgame)
    {
        if (popcount(board.get(color, BISHOP)) >= 2)
            return endgame ? 55 : 45;

        return 0;
    }

    int rooks_on_open_files(Chessboard& board, Color color, bool endgame)
    {
        int bonus = 0;
        Bitboard file = FileABB;

        for (int i = 0; i < 8; i++)
        {
            if (board.get(color, ROOK) & file)
            {
                if ((file & board.get(color, ROOK)) == (file
                & (board.get(BLACK, ALL) | board.get(WHITE, ALL))))
                {
                    bonus += endgame ? 40 : 20;
                }

                else if ((file & board.get(color, ROOK)) == (file
                & (board.get(color, ALL))))
                {
                    bonus += endgame ? 20 : 10;
                }
            }
            file = file << 1;
        }

        return bonus;
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
            if (endgame)
            {
                score += get_position_score(pawns_mobility_endgame_bonus,
                                            square, color);
            }
            else
            {
                score +=
                    get_position_score(pawns_mobility_bonus, square, color);
            }
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
            if (endgame)
            {
                score += get_position_score(rooks_mobility_endgame_bonus,
                                            square, color);
            }
            else
            {
                score +=
                    get_position_score(rooks_mobility_bonus, square, color);
            }
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

    int evaluate(Chessboard& board)
    {
        int score = 0;

        bool endgame = false;

        if (popcount(board.get(BLACK, ALL) | board.get(WHITE, ALL)) < 10)
            endgame = true;

        Color color;
        Color other_color;

        color = board.current_color();
        other_color = opposite_color(color);

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
                * (get_material_score(QUEEN, endgame));

        score += (popcount(board.get(color, KNIGHT)))
                * (get_material_score(KNIGHT, endgame));

        score += (popcount(board.get(color, BISHOP)))
                * (get_material_score(BISHOP, endgame));

        score += (popcount(board.get(color, ROOK)))
                * (get_material_score(ROOK, endgame));

        score += (popcount(board.get(color, PAWN)))
                * (get_material_score(PAWN, endgame));


        // Bonus from position
        score += get_position_bonus(board, color, endgame);

        score -= get_position_bonus(board, other_color, endgame);

        // Bishop pair bonus
        score += bishop_pair_bonus(board, color, endgame);

        score -= bishop_pair_bonus(board, other_color, endgame);

        // Rooks on open file
        score += rooks_on_open_files(board, color, endgame);

        score -= rooks_on_open_files(board, other_color, endgame);

        return score;
    }

} // namespace board
