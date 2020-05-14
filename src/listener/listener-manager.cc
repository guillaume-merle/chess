#include <dlfcn.h>
#include <iostream>

#include "listener-manager.hh"

namespace listener
{
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

    void ListenerManager::notify(void (Listener::*func)())
    {
        for (auto listener : listeners_)
        {
            (listener->*func)();
        }
    }
} // namespace listener
