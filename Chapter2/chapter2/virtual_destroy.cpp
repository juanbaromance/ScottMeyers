// Scott Meyers on item 7 virtual destruction
// meanwhile black magics on vtables, interfaces and wizards

#include <iostream>
#include <typeinfo>
#include <boost/format.hpp>
#include <tr1/regex>

template <typename T>
class iClock {
public:
    virtual T getValueOfTime() = 0;
    virtual ~iClock() = 0;
};
template<> iClock<std::string>::~iClock(){}

class SClock : public iClock<std::string>
{
public:
    SClock() : hash( typeid(this).hash_code() ) {}
    ~SClock(){ ( std::cout << boost::format("%s(%x)\n") % __PRETTY_FUNCTION__ % hash ).flush(); }
    size_t hash;
private:
    std::string getValueOfTime() override { return typeid(this).name(); }
};

class CClock
{
public:
    CClock() : hash( typeid(this).hash_code() ) {}
    const size_t hash;
};

extern "C" void f( void *arg )
{
    size_t *explode = ( size_t* )arg;
    ( std::cout << boost::format("%20s(%x)\n") % __PRETTY_FUNCTION__ % explode[ 0 ] ).flush();
    explode[ 0 ]++;
}

int main()
{
    iClock<std::string> *clock = new SClock();
    ( std::cout << boost::format("%20s\n") % clock->getValueOfTime() ).flush();

    CClock s;
    ( std::cout << boost::format("%20s(%x)\n") % __PRETTY_FUNCTION__ % s.hash ).flush();
    f( ( void* )( & s ) );
    ( std::cout << boost::format("%20s(%x)\n") % __PRETTY_FUNCTION__ % s.hash ).flush();

    delete clock;
}
