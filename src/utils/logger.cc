#include "logger.hh"

Logger::Logger()
{
    file_.open("/tmp/chess.log");
    open_ = file_.is_open();
}

Logger::~Logger()
{
    file_.close();
}
