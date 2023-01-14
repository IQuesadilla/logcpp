#include "logcpp.h"
#include "sstream"

void lifetimelogcpp::operator<<(const char *output)
{
    logobj->log(output);
}

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
    indent();
    std::cout << "Log: " << output << std::endl;
}

lifetimelogcpp logcpp::function(const char *name)
{
    indent();
    std::cout << "Function: (" << name << ")" << std::endl;
    ++tabs;
    return lifetimelogcpp(this);
}

void logcpp::endfunc()
{
    --tabs;
}

void logcpp::indent()
{   
    std::stringstream os;
    for (int i = 0; i < tabs; ++i)
    {
        os << "  ";
    }
    std::cout << os.str();
}