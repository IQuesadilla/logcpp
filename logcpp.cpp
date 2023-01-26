#include "logcpp.h"
#include "sstream"
#include <iostream>

logcpp::logcpp(vlevel verbosity)
{
    tabs = 0;
    _verbosity = verbosity;
}

logcpp::~logcpp()
{
    ;
}

void logcpp::flush(loglevel lev, const char *output)
{
    std::stringstream templogstream;

    templogstream << indent();

    switch (_verbosity)
    {
        case DEBUG:
            // Allow all on debug
        break;
        case VV:
            if (lev == FUNCTION ||
                lev == NOTEDEBUG ||
                lev == VALUEDEBUG) return;
        break;
        case V:
            if (lev == NOTEVV ||
                lev == VALUEVV) return;
        break;
        case DEFAULT:
            if (lev == NOTEV ||
                lev == VALUEV) return;
        break;
    }

    switch (lev)
    {
        case NOTE:
        case NOTEV:
        case NOTEVV:
        case NOTEDEBUG:
            templogstream << "Note: ";
            break;
        case VALUE:
        case VALUEV:
        case VALUEVV:
        case VALUEDEBUG:
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

    templogstream << output << std::endl;

    output_lock.lock();
    std::cout << templogstream.str();
    output_lock.unlock();
}

lifetimelogcpp logcpp::function(const char *name)
{
    std::stringstream templogstream;
    templogstream << "(" << name << ")";
    flush(loglevel::FUNCTION,templogstream.str().c_str());
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
    buff.log(output);
    return buff;
}

lifetimelogcpp & operator<<(lifetimelogcpp &buff, const std::string output)
{
    buff.log(output.c_str());
    return buff;
}

lifetimelogcpp & operator<<(lifetimelogcpp &buff, const int output)
{
    buff.log(std::to_string(output).c_str());
    return buff;
}

lifetimelogcpp & operator<<(lifetimelogcpp &buff, logcpp::loglevel lev)
{
    buff.logobj->flush(lev,buff.logstream.str().c_str());

    buff.logstream.str("");
    buff.logstream.clear();

    return buff;
}

void lifetimelogcpp::log(const char *output)
{
    logstream << output;
}
