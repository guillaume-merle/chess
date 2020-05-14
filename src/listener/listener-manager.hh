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
        ListenerManager() = default;

        ListenerManager(std::vector<std::string> paths);

        void play_ai();

        void close_listeners();

        void notify(void (Listener::*func)());

        void register_board(board::Chessboard& board);

    private:
        std::vector<Listener*> listeners_;

        board::Chessboard chessboard_;
    };

    extern ListenerManager listener_manager;
} // namespace listener
