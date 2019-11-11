// Scott Meyers Chapter 7 on Items 44/45/46/47

#include <iostream>
#include "main.hpp"



template <typename T, typename U>
class Rational {
public:
    Rational( const T & numerator = 0, const U & denominator = 1) : n_ ( numerator ), d_( denominator ) {}
    const T numerator() const { return n_ ; }
    const U denominator() const { return d_ ; }
    const T n_ ;
    const U d_ ;
    const Rational & dump()
    {
        report( std::string( __PRETTY_FUNCTION__ ) + " : " + std::to_string(n_) + "/" + std::to_string(d_ ));
        return *this;
    }
};

int main()
{
    // c++17 extracts the Rational<T> from right side types
    Rational oneHalf( Rational(1,2).dump() );
    return 0;
}


