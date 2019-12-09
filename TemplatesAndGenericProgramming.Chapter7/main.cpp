// Scott Meyers Chapter 7 Templates and Generic Programming on items

// 44 Factor parameter-independent code out of templates.
// 45 Use member function templates to accept all compatible types
// 46 Define non-member functions inside templates when type conversions are desired.


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

    friend const Rational<T,U> operator*(const Rational<T,U>& lhs, const Rational<T,U>& rhs);
};

template<typename T,typename U>
const Rational<T,U> operator*(const Rational<T,U>& lhs, const Rational<T,U>& rhs)
{ return Rational<T,U>(); }


int main()
{
    // c++17 extracts the Rational<T> from right side types
    Rational(1,2).dump();
    return 0;
}


