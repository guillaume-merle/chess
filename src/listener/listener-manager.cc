#include <dlfcn.h>

#include "listener-manager.hh"

namespace listener
{
    ListenerManager::ListenerManager(std::vector<Listener> listeners)
        : listeners_(listeners)
    {
        chessboard_ = board::Chessboard();
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
} // namespace listener
