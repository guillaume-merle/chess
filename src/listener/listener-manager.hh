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

        void close_listeners();
    
    private:

        std::vector<Listener> listeners_;
        board::Chessboard chessboard_;
    };
} // namespace listener
