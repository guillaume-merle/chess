#include <dlfcn.h>
#include <iostream>

#include "listener-manager.hh"


namespace listener
{
    ListenerManager listener_manager;

    ListenerManager::ListenerManager(std::vector<std::string> paths)
    {
        for (auto path = paths.begin(); path != paths.end(); ++path)
        {
            void* handle = dlopen(path->c_str(), RTLD_LAZY);
            if (!handle)
                std::cerr << "Cannot open library: " << dlerror() << '\n';
            else
            {
                void* symbol = dlsym(handle, "listener_create");
                Listener* listener = reinterpret_cast<Listener*(*)()>(symbol)();
                listeners_.push_back(listener);
            }
        }
    }

    void ListenerManager::play_ai()
    {}

    void ListenerManager::close_listeners()
    {
        for (size_t i = 0; i < listeners_.size(); ++i)
        {
            dlclose(listeners_.at(i));
        }
    }

    void ListenerManager::register_board(board::Chessboard& board)
    {
        chessboard_ = board;

        for (auto listener : listeners_)
        {
            listener->register_board(board);
        }
    }

    void ListenerManager::notify(void (Listener::*func)(board::Color),
                                 board::Color color)
    {
        for (auto listener : listeners_)
        {
            (listener->*func)(color);
        }
    }

    void ListenerManager::notify(void (Listener::*func)())
    {
        for (auto listener : listeners_)
        {
            (listener->*func)();
        }
    }

    void ListenerManager::notify(void (Listener::*func)(const board::PieceType,
                                                        const board::Position&,
                                                        const board::Position&),
                                 const board::PieceType& piece,
                                 const board::Position& from,
                                 const board::Position& to)
    {

        for (auto listener : listeners_)
        {
            (listener->*func)(piece, from, to);
        }
    }

    void ListenerManager::notify(void (Listener::*func)(const board::PieceType,
                const board::Position&),
            const board::PieceType& piece,
            const board::Position& at)
    {
        for (auto listener : listeners_)
        {
            (listener->*func)(piece, at);
        }
    }
} // namespace listener
