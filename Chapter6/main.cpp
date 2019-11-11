// Scott Meyers Chapter 6 on Items 34

#include <iostream>
#include <typeinfo>
#include <vector>
#include <list>
#include <string>
#include <boost/format.hpp>

#include <memory>
#include <ctime>
#include <boost/format.hpp>
template <typename ...>
void report( const std::string & backtrace, ... )
{
    ( std::cout << backtrace << " " << "\n").flush();
}

template <typename T>
struct crtp {
    T& underly(){ return static_cast<T&>(*this); }
    T const& underly() const { return static_cast<T const&>(*this); }
};

// pseudo interface :: draw stuff
template <typename T>
class Shape : public crtp<T> {
public:

    virtual void draw() = 0;
    virtual std::string name() = 0;
    virtual void error( const std::string & backtrace = "")
    {
        this->underly().dump( backtrace );
    }
    size_t ObjectID() { return this->underly().stamp(); } // this really means that the object identification is singled mode aka it is an invariant of the classes tree
    virtual ~Shape(){ report( __PRETTY_FUNCTION__ ); }

};


class Rectangle : public Shape<Rectangle> {
public:
    void draw() override { report( __PRETTY_FUNCTION__ ); }
    void dump( const std::string backtrace ){ report( backtrace ); }
    size_t stamp(){ return typeid(this).hash_code(); }

private:
    std::string name() override { return typeid(this).name(); }
};


class Ellipse : public Shape<Ellipse> {
public :
    virtual double valueOfarea() = 0;
    void dump(const std::string backtrace ) { report( backtrace ); }

private:
    std::string name() override { return typeid(this).name(); }
};

double Ellipse::valueOfarea(){ return 100.32; }

class Ellipse1 : public Ellipse
{
public:
    double valueOfarea() override { return Ellipse::valueOfarea(); }
    void draw() override {}
};

int main()
{
    std::unique_ptr<Shape<Rectangle>> r( std::make_unique<Rectangle>() );
    r->draw();
    r->error( ( boost::format("%s(%08x)") % r->name() % r->ObjectID() ).str() );
    std::unique_ptr<Ellipse1> e( std::make_unique<Ellipse1>() );
    e->dump( std::to_string( e->valueOfarea() ) );
    return 0;
}


