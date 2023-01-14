#include "../logcpp.h"

void otherfunc(logcpp *log)
{
    auto func2 = log->function("newfunc");
    func2 << "Here inside";
}

int main(int argc, char **argv)
{
    logcpp temp;
    auto func1 = temp.function("main");
    func1 << "Here outer";
    otherfunc(&temp);
    func1 << "Here outer again";
}