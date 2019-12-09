#include "MyPersonImpl.h"
#include "MyPerson.h"
#include <boost/format.hpp>
#include <iostream>

MyPersonView::MyPersonView () :
    pImpl( std::make_shared< MyPersonImpl >( ) )
{

}


void MyPersonView::audit()
{
    pImpl->audit( __PRETTY_FUNCTION__ );
}
