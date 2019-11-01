#include <memory>
#include <boost/format.hpp>
#include <iostream>

class iA {
public:
    iA()
    {
        startup();
    }

    virtual void dump() = 0;
    virtual ~iA() = 0;

private:
    void startup(){
        //    dump();
    }
};

iA::~iA(){}

class A : public iA {
public:
    // Error prone not... even more
    A( int p1 = 0, int p2 = 0 ) : _p1(p1), _p2(p2){}

    /* Proper parametrization */
    A& p1( int tmp ){ _p1 = tmp; return *this; }
    A& p2( int tmp ){ _p2 = tmp; return *this; }

    void dump() override
    {
        ( std::cout << boost::format("%s(%03d,%03d)(%p)\n") % __PRETTY_FUNCTION__ % _p1 % _p2 % this ).flush();
    }

private:
    int _p1,_p2;
};

int main()
{
    { std::shared_ptr<iA> a = std::make_shared<A>(0,-1); }

    A a;
    a.dump();

    a.p1( -3 ).p2( -1 );
    a.dump();
}
