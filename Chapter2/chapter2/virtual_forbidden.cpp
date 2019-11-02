// item 9 Proof on virtual call undefined behaviour when requested on the construction phase
// item 10 Application on monadics smelling returning self rererences, same as operator = , copy constructor t
// extra stuff: templates acting as interfaces through static polymorphism, sohemow a crtp

#include <memory>
#include <boost/format.hpp>
#include <iostream>

template <typename T1, typename T2>
class iA {
public:
    iA(){ startup(); }

    virtual T1& dump() = 0;
    virtual ~iA(){};

    /* Proper parametrization */
    virtual T1& x( const T2 & tmp ) = 0;
    virtual T1& y( const T2 & tmp ) = 0;

private:
    void startup()
    {
        // uncoment below to die
        // dump();
    }
};


// derivated class and customization are both injected as a Template params
// into the interface

template<typename T=int>
class A : public iA< A<T>, T > {
public:
    // Error prone not... even more
    A( T x = 0, T y = 0 ) : _x(x), _y(y){}

    /* Proper parametrization */
    A<T>& x( const T & tmp )override { _x = tmp; return *this; }
    A<T>& y( const T & tmp )override { _y = tmp; return *this; }
    A<T>& dump() override
    {
        ( std::cout << boost::format("%s(%03d,%03d)(%p)\n") % __PRETTY_FUNCTION__ % _x % _y % this ).flush();
        return *this;
    }

private:
    T _x, _y;
};

int main()
{
    std::shared_ptr<iA<A<>,int>> a = std::make_shared<A<>>(0,-1);
    a->x( -3 ).dump().y( -5 ).dump();
}
