#pragma once

#include <fstream>

class Logger
{
public:
    Logger();

    ~Logger();

    template <typename T>
    Logger& operator<<(const T& obj)
    {
        if (open_)
        {
            file_ << obj;
            file_.flush();
        }

        return *this;
    }

private:
    bool open_;

    std::ofstream file_;
};

extern Logger logger;
