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

        void notify(void (Listener::*func)(board::Color), board::Color color);

        void notify(void (Listener::*func)());

        void notify(void (Listener::*func)(const board::PieceType,
                                           const board::Position&,
                                           const board::Position&),
                    const board::PieceType& piece,
                    const board::Position& from,
                    const board::Position& to);

        void notify(void (Listener::*func)(const board::PieceType,
                                           const board::Position&),
                    const board::PieceType& piece,
                    const board::Position& at);

        void register_board(board::Chessboard& board);

    private:
        std::vector<Listener*> listeners_;

        board::Chessboard chessboard_;
    };

    extern ListenerManager listener_manager;
} // namespace listener
