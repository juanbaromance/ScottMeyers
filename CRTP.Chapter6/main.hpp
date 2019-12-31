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

template <typename T, template<typename> class CRTPType>
struct crtp {
    T& underly(){ return static_cast<T&>(*this); }
    T const& underly() const { return static_cast<T const&>(*this); }
private:
    crtp(){}
    friend CRTPType<T>;
};

// pseudo interface :: using static and dynamic modalities
template <typename T>
class Shape : public crtp<T,Shape> {

public:
    static constexpr const char* default_name = "UnknownShape";

    /* RT Polymorphic model */
    virtual std::string name( const std::string & name_ = default_name ) = 0;

    /* CRTP Polymorphic model */
    virtual void dump( const std::string & backtrace = ""){ this->underly().dump_impl( name() + backtrace ); }
    virtual void draw(){ this->underly().draw_impl(); }

    size_t ObjectID() { return this->underly().stamp(); } // this really means that the object identification is singled mode aka it is an invariant of the classes tree
    virtual ~Shape(){ report( __PRETTY_FUNCTION__ ); }

private:
    friend T;

    /* Default implementations */
    void draw_impl(){ report( __PRETTY_FUNCTION__  ); }
    void dump_impl( const std::string & backtrace = ""){ report( __PRETTY_FUNCTION__  + backtrace ); }
    std::string name_ {""};
};



/* Default method implementation if the template is Run Time virtualised affect */
template <typename T>
std::string Shape<T>::name( const std::string & name__ )
{
    return ( ( name__ == Shape<T>::default_name ) ? name_ : ( name_ = "." + name__ ) ) ;
}

class Rectangle : public Shape<Rectangle> {
    friend Shape<Rectangle>;

public:
    size_t stamp(){ return typeid(this).hash_code(); }

private:
    void draw_impl() { report( __PRETTY_FUNCTION__ ); }
    void dump_impl( const std::string & backtrace ){ report( backtrace ); }
    std::string name( const std::string & name_ ) override { return Shape::name( name_ ); }
};


// Purpose of valueOfarea specification :: implementators MUST provide a method, however a Default Method is already provided right here
template<typename T>
class Ellipse : public Shape<Ellipse<T>> {
public :
    double valueOfarea(){ return 100.32; }
    std::string name( const std::string & name_ ) override { return Shape<Ellipse<T>>::name( name_ ); }

private:
    friend Shape<Ellipse>;
    void dump_impl(const std::string & backtrace ){ report( backtrace ); }
    void draw_impl(){ static_cast<T&>(*this).draw_ellipses();}
    void draw_ellipses(){ report( __PRETTY_FUNCTION__ );  }

};

class Ellipse1 : public Ellipse<Ellipse1>
{
    friend Ellipse;

public:
    double valueOfarea() { return Ellipse<Ellipse1>::valueOfarea(); }
    void draw_ellipses()
    {
        if( Shape::name() == "" )
            name( typeid(*this).name() );
        dump( ( boost::format(".(%s)" ) % __PRETTY_FUNCTION__  ).str() );
    }
};

class Ellipse2 : public Ellipse<Ellipse2>
{
    friend Ellipse;
};
