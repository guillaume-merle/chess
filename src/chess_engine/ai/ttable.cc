#include "ttable.hh"

namespace ai
{
    bool TTable::insert(uint64_t key, int depth, int score,
                        TTableEntryFlag flag, Move& bestmove)
    {
        int hashkey = key % TTable::max_size_;
        auto it = map_.find(hashkey);

        if (it != map_.end())
        {
            // handle collisions with depth replacement scheme
            if (it->second.bucket_size_ >= TTable::bucket_max_size_)
            {
                int bucket_index = 0;

                while (bucket_index < TTable::bucket_max_size_)
                {
                    if (depth >= it->second.depth_)
                    {
                        auto new_entry = TTableEntry(key, depth, score, flag,
                                                     bestmove);
                        it->second = new_entry;
                        return true;
                    }

                    ++it;
                    bucket_index += 1;
                }

                // didn't insert anything
                return false;
            }
            else
            {
                hashkey += it->second.bucket_size_;
                it->second.bucket_size_ += 1;
            }
        }

        auto entry = TTableEntry(key, depth, score, flag,
                                 bestmove);
        map_.insert({hashkey, entry});
        return true;
    }

    std::optional<TTableEntry*> TTable::at(uint64_t key, int depth)
    {
        int hashkey = key % TTable::max_size_;
        auto it = map_.find(hashkey);

        if (it == map_.end())
            return {};

        int bucket_index = 0;
        while (bucket_index < bucket_max_size_ and it->second.key_ != key)
        {
            bucket_index += 1;
            ++it;
        }

        // get the entry only if the depth corresponds to the requirement
        if (it->second.key_ == key and it->second.depth_ >= depth)
            return &it->second;

        return {};
    }

    void TTable::clear()
    {
        map_.clear();
    }

} // namespace ai
