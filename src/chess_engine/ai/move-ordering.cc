#include <algorithm>

#include "move-ordering.hh"
#include "evaluation.hh"

namespace ai
{
    int MoveOrdering::mvv_lva_[5][6];

    MoveOrdering::MoveOrdering(std::vector<Move>& moves)
        : moves_(moves)
    {
        grade_moves_();
        order_moves_();
    }

    void MoveOrdering::init()
    {
        int score = 5 * 6;
        // Victims: Queen, Rook, Bishop, Knight, Pawn
        for (int i = 0; i < 5; i += 1)
        {
            // Aggressors: Queen, Rook, Bishop, Knight, Pawm, King
            for (int j = 5; j >= 0; j -= 1)
            {
                MoveOrdering::mvv_lva_[i][j] = score;
                score -= 1;
            }
        }
    }

    std::vector<Move>& MoveOrdering::get()
    {
        return moves_;
    }

    void MoveOrdering::grade_moves_()
    {
        // TODO: add PV-move, killer moves (Transposition Table)
        for (auto& move : moves_)
        {
            // set capture grade via base grade + MVV-LVA score
            if (move.is_capture())
                move.set_grade(Grade::CAPTURE
                        + mvv_lva_[move.get_capture()][move.get_piece()]);
            // TODO: use material value of the piece
            else if (move.is_promotion())
                move.set_grade(Grade::PROMOTION
                        + get_material_score(move.get_promotion()));
            // add history heuristic
            else
                move.set_grade(0);
        }
    }

    void MoveOrdering::order_moves_()
    {
        std::sort(moves_.begin(), moves_.end(), [](Move& a, Move& b) {
            return a.get_grade() > b.get_grade();
        });
    }
}
