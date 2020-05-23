#include "move-heuristics.hh"

namespace ai
{
    MoveHeuristics::MoveHeuristics(TTable* ttable)
        : history_{{{0}}}, killer_{}, ttable_(ttable)
    {}

    Move MoveHeuristics::get_killer(int depth, unsigned number) const
    {
        if (depth > killers_depth_ or number > 1)
            return Move();

        return killer_[depth][number];
    }

    void MoveHeuristics::set_killer(Move move, int depth)
    {
        if (depth >= killers_depth_)
            return;

        // if there is already a killer_move, move it to second and replace it
        Move& killer_move = killer_[depth][0];
        if (not killer_move.is_none())
        {
            killer_[depth][1] = killer_move;
        }

        // set the first killer move
        killer_[depth][0] = move;
    }

    void MoveHeuristics::set_history(Color color, Move& move, int depth)
    {
        history_[color][move.get_from()][move.get_to()] += depth * depth;
    }

    int MoveHeuristics::get_history(Color color, Move& move) const
    {
        return history_[color][move.get_from()][move.get_to()];
    }

    TTable* MoveHeuristics::get_transposition_table()
    {
        return ttable_;
    }

} // namespace ai
