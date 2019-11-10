#pragma once
#include <string>

class MyPersonImpl
{
public:
    MyPersonImpl(const std::string & name = "unknown ");
    void audit( const std::string & backtrace );

    std::string name_ ;
};

