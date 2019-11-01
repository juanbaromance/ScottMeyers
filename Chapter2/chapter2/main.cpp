// Scott Meyers Chapter 2 on Items 5 and 6 constructors, asignments, const and references
// Widget will be whatever you mean
// Lets do a controlled implementation which provides a pseudo-copied Object.

#include <iostream>
#include <typeinfo>
#include <vector>
#include <list>
#include <boost/format.hpp>


template< typename T>
class Widget
{
public:
    Widget( const std::string& name, const T& id)
        : r_name( const_cast<std::string&>(name) ), id_val(id){ }
    void whoAmI( const std::string & backtrace ="") const {
        ( std::cout << ( boost::format("%s.%s.%2d :: (%p)(%s)\n")
                       % typeid(*this).name()
                       % r_name % id_val % this
                       % ( backtrace ) ) ).flush();
    }

    // custom asignment operator where only the modifyable part of source object is copied to *this
    Widget& operator=( const Widget & source )
    {
        this->r_name = source.r_name;
        return *this;
    }
    std::string & name() { return r_name; }

private:
    std::string& r_name;
    const T id_val;
};

int main()
{
    using MyWidget = Widget<int>;
    std::string p_name("MyPWidget");
    MyWidget p( p_name, 5);

    {
        auto s = p;
        s.whoAmI("s_aliased");
        p.whoAmI();
    }

    {
        std::string s_name("MySWidget");
        MyWidget s( s_name, 15);
        std::string graft( p.name() + ".former");
        p = s;
        s.whoAmI( );
        p.whoAmI( graft );

    }

    return 0;
}
