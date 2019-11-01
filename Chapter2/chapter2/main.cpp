// Scott Meyers Chapter 2 on Items 5 and 6 constructors, asignments, const and references

#include <iostream>
#include <typeinfo>
#include <vector>
#include <list>
#include <boost/format.hpp>
#include <boost/core/noncopyable.hpp>

// Lets build an object network where the explicit copy effect must be FORBIDDEN
// Lets also introduce howto solve the diamond case of use on Polymorphism
class unCopyable {
public:
    // virtual const std::string diamondResolver() = 0;
    virtual const std::string diamondResolver() { return typeid(this).name(); };

protected:
    unCopyable( const std::string& parent ) : _parent( parent ){}
    ~unCopyable(){}

private:
    const std::string& _parent;
    unCopyable(const unCopyable &) = delete;
};

class HLayer1 : virtual protected unCopyable
{
public:
    HLayer1() : unCopyable( __FUNCTION__ ) {}
    virtual ~HLayer1(){}
};

class HLayer2 : virtual protected unCopyable
{
public:
    HLayer2() : unCopyable( __FUNCTION__ ) {}

protected:
    virtual ~HLayer2(){}
    const std::string diamondResolver() override { return typeid(this).name(); };
};


class Client : public HLayer1, public HLayer2
{
public:
    Client( const std::string& name ) : unCopyable( __FUNCTION__ ), r_name( const_cast<std::string&>(name) )
    {

    }

    void testDiamondAntiPattern()
    {
        ( std::cout << ( boost::format("\n%s :: %s %s)\n")
                       % __PRETTY_FUNCTION__  % diamondResolver() % r_name )).flush() ;
    }

private:
    std::string& r_name;
};

class OtherClient : boost::noncopyable {
public:
    void whoAmI( const std::string & backtrace ="") const
    {
        ( std::cout << ( boost::format("%s.%s :: (%p)(%s)\n")
                       % typeid(*this).name()
                       % r_name % this
                       % ( backtrace ) ) ).flush();
    }
    OtherClient( const std::string& name = "unknown" ) : r_name( const_cast<std::string&>(name) ) {}

private:
    std::string& r_name;
};

// Widget will be whatever you mean
// Lets do a controlled implementation which provides a pseudo-copied Object.
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

    Client myClient("MyClient");
    myClient.testDiamondAntiPattern();

    std::string name("MyOtherClient");
    OtherClient myOtherClient(name), test;
    myOtherClient.whoAmI();
    test.whoAmI();
    // test = myOtherClient;
    return 0;
}
