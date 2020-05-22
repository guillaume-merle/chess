#include "ttable-entry.hh"

namespace ai
{
    TTableEntry::TTableEntry(uint64_t key, int depth, int score,
                             TTableEntryFlag flag, Move& bestmove)
        : key_(key), depth_(depth), score_(score), flag_(flag)
          , bestmove_(bestmove)
    {}

    std::optional<int> TTableEntry::get_bounded_score(int& alpha, int& beta)
    {
        if (flag_ == TTableEntryFlag::EXACT)
            return score_;
        else if (flag_ == TTableEntryFlag::ALPHA)
            alpha = std::max(score_, alpha);
        else
            beta = std::min(score_, beta);

        if (alpha >= beta)
            return score_;

        return {};
    }
}
