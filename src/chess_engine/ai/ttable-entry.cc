#include "ttable-entry.hh"

namespace ai
{
    TTableEntry::TTableEntry(uint64_t key, int depth, int score,
                             TTableEntryFlag flag, Move& bestmove)
        : key_(key), depth_(depth), score_(score), flag_(flag)
          , bestmove_(bestmove)
    {}
}
