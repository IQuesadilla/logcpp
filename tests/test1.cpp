#include "../logcpp.h"
#include <memory>
#include <sstream>

void otherfunc(std::shared_ptr<logcpp> logobj)
{
    auto func2 = logobj->function("newfunc");
    func2 << "Here inside" << logcpp::loglevel::NOTE;
}

int main(int argc, char **argv)
{
    std::shared_ptr<logcpp> logobj;
    logobj.reset(new logcpp(logcpp::vlevel::DEBUG));

    auto log = logobj->function("main");
    log << "Here outer" << logcpp::loglevel::NOTE;

    otherfunc(logobj);
    
    log << "The number six: " << 6 << logcpp::loglevel::VALUE;
    log << "This is a warning" << logcpp::loglevel::WARNING;
    log << "Here is an error" << logcpp::loglevel::ERROR;
}