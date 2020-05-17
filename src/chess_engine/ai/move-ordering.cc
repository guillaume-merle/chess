#include "move-ordering.hh"

namespace ai
{
    int MoveOrdering::mvv_lva_[5][6];

    MoveOrdering::MoveOrdering(std::vector<Move>& moves)
        : moves_(moves)
    {}

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
}
