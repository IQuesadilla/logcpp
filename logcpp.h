#ifndef LOGCPP_H
#define LOGCPP_H
#pragma once

class lifetimelogcpp;

class logcpp
{
public:
    logcpp();
    ~logcpp();

    void log(const char *output);
    
    lifetimelogcpp function(const char *name);
    void endfunc();

private:
    const char *indent();
    int tabs;
};

class lifetimelogcpp
{
public:
    lifetimelogcpp(logcpp *log) { logobj = log; }
    ~lifetimelogcpp() { logobj->endfunc(); }

    friend lifetimelogcpp &operator<<(lifetimelogcpp &stream, const char *output);
    friend lifetimelogcpp &operator<<(lifetimelogcpp &stream, const int output);
    friend lifetimelogcpp &operator<<(lifetimelogcpp &stream, lifetimelogcpp &output);

    lifetimelogcpp &operator<<(lifetimelogcpp &stream);

protected:
    logcpp *logobj;
};

lifetimelogcpp &iendl(lifetimelogcpp &stream);

#endif