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

        ListenerManager(std::vector<Listener> listeners);

        void play_ai();

        void close_listeners();
    
    private:

        std::vector<Listener> listeners_;
        board::Chessboard chessboard_;
    };
} // namespace listener
