#include "ttable.hh"

namespace ai
{
    void TTable::insert(uint64_t key, int depth, int score,
                        TTableEntryFlag flag, Move& bestmove)
    {
        auto new_entry = std::make_shared<TTableEntry>(depth, score, flag,
                                                     bestmove);
        map_[key] = new_entry;
    }

    std::shared_ptr<TTableEntry> TTable::at(uint64_t key, int depth)
    {
        auto it = map_.find(key);
        if (it != map_.end() && it->second->depth_ >= depth)
            return it->second;
        return nullptr;
    }

    void TTable::clear()
    {
        map_.clear();
    }

} // namespace ai
