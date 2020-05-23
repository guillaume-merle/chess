#include "move-heuristics.hh"

namespace ai
{
    MoveHeuristics::MoveHeuristics(TTable* ttable)
        : history_{{{0}}}, killer_{}, ttable_(ttable)
    {}

    Move MoveHeuristics::get_killer(int depth) const
    {
        if (depth > killers_depth_)
            return Move();

        return killer_[depth];
    }

    void MoveHeuristics::set_killer(Move move, int depth)
    {
        if (depth >= killers_depth_)
            return;

        killer_[depth] = move;
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
