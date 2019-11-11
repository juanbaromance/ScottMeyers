#pragma once

#include <typeinfo>
#include <string>
#include <iostream>
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

// pseudo interface :: using static and dynamic modalities
template <typename T>
class Shape : public crtp<T> {

public:
    static const std::string default_name;

    /* RT Polymorphic model */
    virtual void draw() = 0;
    virtual std::string name( const std::string & name_ = default_name ) = 0;

    /* CRTP model */
    virtual void dump( const std::string & backtrace = "")
    {
        this->underly().dumpShape( name() + backtrace );
    }
    size_t ObjectID() { return this->underly().stamp(); } // this really means that the object identification is singled mode aka it is an invariant of the classes tree
    virtual ~Shape(){ report( __PRETTY_FUNCTION__ ); }

private:
    std::string name_ {""};
};

template <typename T>
const std::string Shape<T>::default_name = "unknown:";

template <typename T>
std::string Shape<T>::name( const std::string & name__ )
{
    return ( ( name__ == Shape<T>::default_name ) ? name_ : ( name_ = "." + name__ ) ) ;
}

class Rectangle : public Shape<Rectangle> {
public:
    void draw() override { report( __PRETTY_FUNCTION__ ); }
    void dumpShape( const std::string backtrace ){ report( backtrace ); }
    size_t stamp(){ return typeid(this).hash_code(); }
    std::string name( const std::string & name_ ) override { return Shape::name( name_ ); }
};


// Purpose of valueOfarea specification :: implementators MUST provide a method, however a Default Method is already provided right here
class Ellipse : public Shape<Ellipse> {
public :
    virtual double valueOfarea() = 0;
    void dumpShape(const std::string backtrace ) { report( backtrace ); }
    std::string name( const std::string & name_ ) override { return Shape::name( name_ ); }
};

double Ellipse::valueOfarea(){ return 100.32; }

class Ellipse1 : public Ellipse
{
public:
    double valueOfarea() override { return Ellipse::valueOfarea(); }
    void draw() override
    {
        if( Shape::name() == "" )
            name( typeid(*this).name() );
        dump( ( boost::format(".(%s)" ) % __FUNCTION__  ).str() );
    }
};

