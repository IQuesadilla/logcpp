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
    std::cout << indent() << output;
}

lifetimelogcpp logcpp::function(const char *name)
{
    std::stringstream ss;
    ss << "Function: (" << name << ")" << "\n";
    log(ss.str().c_str());
    ++tabs;
    return lifetimelogcpp(this);
}

void logcpp::endfunc()
{
    --tabs;
}

const char *logcpp::indent()
{   
    std::stringstream os;
    for (int i = 0; i < tabs; ++i)
    {
        os << "  ";
    }
    return os.str().c_str();
}

lifetimelogcpp &operator<<(lifetimelogcpp &stream, const char *output)
{
    std::stringstream ss;
    ss << "Log: " << output << "\n";
    stream.logobj->log(ss.str().c_str());
    return stream;
}

lifetimelogcpp &operator<<(lifetimelogcpp &stream, const int output)
{
    std::stringstream ss;
    ss << "Value: " << output << "\n";
    stream.logobj->log(ss.str().c_str());
    return stream;
}

lifetimelogcpp &operator<<(lifetimelogcpp &stream, lifetimelogcpp &output)
{
    //std::stringstream ss;
    //ss << "Value: " << output << "\n";
    //stream.logobj->log(ss.str().c_str());
    return stream;
}