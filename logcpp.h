#ifndef LOGCPP_H
#define LOGCPP_H
#pragma once

#include <sstream>

class lifetimelogcpp;

class logcpp
{
public:
    enum loglevel
    {
        NOTE,
        VALUE,
        WARNING,
        ERROR,
        FUNCTION
    };

    logcpp();
    ~logcpp();

    void log(const char *output);
    void flush(loglevel lev);
    lifetimelogcpp function(const char *name);
    void endfunc();

private:
    std::string indent();

    std::stringstream logstream;
    int tabs;
};

class lifetimelogcpp
{
public:
    lifetimelogcpp(logcpp *log) { logobj = log; }
    ~lifetimelogcpp() { logobj->endfunc(); }

    friend lifetimelogcpp & operator<<(lifetimelogcpp &buff, const char *output);
    friend lifetimelogcpp & operator<<(lifetimelogcpp &buff, const std::string output);
    friend lifetimelogcpp & operator<<(lifetimelogcpp &buff, const int output);
    friend lifetimelogcpp & operator<<(lifetimelogcpp &buff, const logcpp::loglevel lev);

private:
    logcpp *logobj;
};

#endif