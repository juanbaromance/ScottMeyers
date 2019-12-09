#pragma once

#include <typeinfo>
#include <string>
#include <iostream>
#include <boost/format.hpp>


template <typename ...>
void report( const std::string & backtrace, ... )
{
    ( std::cout << backtrace << " " << "\n").flush();
}
