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


    std::vector<Move> TTable::principal_variation(Chessboard board, int depth)
    {
        std::vector<Move> variations;
        variations.reserve(depth);

        for (int i = 0; i < depth; i += 1)
        {
            auto ttentry = this->at(board.get_zobrist_key());
            if (not ttentry)
                break;

            Move& move = ttentry->get_bestmove();
            variations.emplace_back(move);
            board.do_move(move);
        }

        return variations;
    }

} // namespace ai
