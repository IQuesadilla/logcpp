#include "logcpp.h"
#include "sstream"
#include <iostream>

logcpp::logcpp()
{
    tabs = 0;
}

logcpp::~logcpp()
{
    ;
}

void logcpp::log(const char *output)
{
    logstream << output;
}

void logcpp::flush(loglevel lev)
{
    std::stringstream templogstream;

    templogstream << indent();

    switch (lev)
    {
        case NOTE:
            templogstream << "Note: ";
            break;
        case VALUE:
            templogstream << "Value: ";
            break;
        case WARNING:
            templogstream << "Warning: ";
            break;
        case ERROR:
            templogstream << "ERROR: ";
            break;
        case FUNCTION:
            templogstream << "Function: ";
            break;
    }

    templogstream << logstream.str() << std::endl;

    logstream.str("");
    logstream.clear();

    output_lock.lock();
    std::cout << templogstream.str();
    output_lock.unlock();
}

lifetimelogcpp logcpp::function(const char *name)
{
    indent();
    logstream << "(" << name << ")";
    flush(loglevel::FUNCTION);
    ++tabs;
    return lifetimelogcpp(this);
}

void logcpp::endfunc()
{
    --tabs;
}

std::string logcpp::indent()
{   
    std::stringstream os;
    for (int i = 0; i < tabs; ++i)
    {
        os << "  ";
    }
    return os.str();
}

lifetimelogcpp & operator<<(lifetimelogcpp &buff, const char *output)
{
    buff.logobj->log(output);
    return buff;
}

lifetimelogcpp & operator<<(lifetimelogcpp &buff, const std::string output)
{
    buff.logobj->log(output.c_str());
    return buff;
}

lifetimelogcpp & operator<<(lifetimelogcpp &buff, const int output)
{
    buff.logobj->log(std::to_string(output).c_str());
    return buff;
}

lifetimelogcpp & operator<<(lifetimelogcpp &buff, logcpp::loglevel lev)
{
    buff.logobj->flush(lev);
    return buff;
}

