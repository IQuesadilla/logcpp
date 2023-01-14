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
    void indent();
    int tabs;
};

class lifetimelogcpp
{
public:
    lifetimelogcpp(logcpp *log) { logobj = log; }
    ~lifetimelogcpp() { logobj->endfunc(); }

    void operator<<(const char *output);

private:
    logcpp *logobj;
};

#endif