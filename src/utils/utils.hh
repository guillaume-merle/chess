#pragma once

#include <vector>

namespace board
{
    template <typename T>
    void operator+=(std::vector<T>& res, const std::vector<T>& to_add)
    {
        res.insert(res.end(), to_add.begin(), to_add.end());
    }
}

