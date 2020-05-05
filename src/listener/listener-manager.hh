#pragma once

#include <vector>

#include "chessboard.hh"
#include "listener.hh"

namespace listener
{

    /**
    ** \brief ListenerManager class.
    */
    class ListenerManager
    {
    public:
        void play_ai();

        Chessboard chessboard_;
    
    privated:

        std::vector<Listener> listeners_;
        Chessboard chessboard_;
    };
} // namespace listener
