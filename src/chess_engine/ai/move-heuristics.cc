#include "move-heuristics.hh"

namespace ai
{
    MoveHeuristics::MoveHeuristics()
        : history_{{{0}}}, killer_{}
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
} // namespace ai
