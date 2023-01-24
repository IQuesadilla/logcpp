#include "../logcpp.h"
#include <memory>
#include <sstream>

void otherfunc(std::shared_ptr<logcpp> logobj)
{
    auto func2 = logobj->function("newfunc");
    func2 << "Here inside";
}

int main(int argc, char **argv)
{
    std::shared_ptr<logcpp> logobj;
    logobj.reset(new logcpp());

    auto func1 = logobj->function("main");
    func1 << "Here outer";

    otherfunc(logobj);
    
    func1 << "Here outer again" << 6 << iendl;
    func1 << iendl;
}