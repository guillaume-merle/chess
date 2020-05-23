#include <algorithm>

#include "move-ordering.hh"
#include "evaluation.hh"
#include "logger.hh"

namespace ai
{
    int MoveOrdering::mvv_lva_[5][6];

    MoveOrdering::MoveOrdering(std::vector<Move>& moves,
                               MoveHeuristics& heuristics,
                               Chessboard& board, int depth)
        : moves_(moves), heuristics_(heuristics), depth_(depth), board_(board)
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
        Move pv;
        auto ttable = heuristics_.get_transposition_table();
        if (ttable)
        {
            auto entry = ttable->at(board_.get_zobrist_key().get());
            if (entry)
                pv = entry->get_bestmove();
        }

        for (auto& move : moves_)
        {
            // set the grade to INF if the move is the pv
            if (move == pv)
                move.set_grade(INF);
            // set capture grade via base grade + MVV-LVA score
            else if (move.is_capture())
                move.set_grade(Grade::CAPTURE
                        + mvv_lva_[move.get_capture()][move.get_piece()]);
            else if (move.is_promotion())
                move.set_grade(Grade::PROMOTION
                        + get_material_score(move.get_promotion()));
            else if (move == heuristics_.get_killer(depth_))
                move.set_grade(Grade::KILLER);
            // history heuristic value
            else
            {
                int history = heuristics_
                                .get_history(board_.current_color(), move);
                move.set_grade(history);
            }
        }
    }

    void MoveOrdering::order_moves_()
    {
        std::sort(moves_.begin(), moves_.end(), [](Move& a, Move& b) {
            return a.get_grade() > b.get_grade();
        });
    }
}
