// Scott Meyers Chapter 3 on Items 14,15,16

#include <iostream>
#include <typeinfo>
#include <vector>
#include <list>
#include <string>
#include <boost/format.hpp>
#include <boost/core/noncopyable.hpp>
#include <memory>
#include <ctime>
#include "MyPerson.h"
// Chapert 31 Minimize compile time. aka Dependencies
#include <chrono>

template <typename Stringable = std::string, typename Numerics = size_t>
class Tuple {
public:
    Tuple( const Stringable && _s, const Numerics && _n ) : n( _n ) , s( _s ) {
        ( std::cout << boost::format("%s\n") % __PRETTY_FUNCTION__  ).flush();
    }
    operator char const *() const { return s.c_str(); }
    Numerics operator()( const Numerics & dummy ) const { return n; }
    const Stringable & operator()() const { return s; }

private:
    Numerics n;
    Stringable s;
};



int main()
{
    using namespace std::chrono_literals;
    auto wait = 10ms;
    std::chrono::milliseconds secs = 1s;

    Tuple t( std::string(__PRETTY_FUNCTION__) , 200.23 );
    char const *p = ( char const * )t;
    auto end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    ( std::cout << boost::format("%s %s:%s( %4d )(%d)\n") %  std::ctime(&end_time) % p % t() % t(0) % ( secs - wait ).count() ).flush();

    MyPersonView my_person;
    my_person.audit();
    return 0;
}
