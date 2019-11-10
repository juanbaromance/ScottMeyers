#include "MyPersonImpl.h"
#include <boost/format.hpp>
#include <iostream>

template <typename ...>
void report( const std::string & backtrace, ... )
{
    ( std::cout << backtrace << " " << "\n").flush();
}

MyPersonImpl::MyPersonImpl( const std::string & name) : name_ (name ) {}


void MyPersonImpl::audit(const std::string &backtrace )
{
    report( ( boost::format( "%s: %s" ) % backtrace % name_ ).str() );
}
