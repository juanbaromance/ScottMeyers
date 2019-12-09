// Scott Meyers
// Chapters 6 Inheritance and Object-Oriented Design(34)
// Item 34: Differentiate between inheritance of interface and inheritance of implementation.
// Chapter 7 Templates and Generic Programming (43/44)
// Item 43: Know how to access names in templatized base classes.
// Item 44: Templates as factories of functionality
//
// CRTP as design pattern implementation of Static Polimorphism (virtual and abstract cases)

#include <iostream>
#include "main.hpp"

int main()
{
    std::unique_ptr<Shape<Rectangle>> r( std::make_unique<Rectangle>() );
    r->name("MyRectangle");
    r->draw();
    r->dump( ( boost::format("(%08x)") % r->ObjectID() ).str() );

    std::unique_ptr<Shape<Ellipse<Ellipse1>>> e( std::make_unique<Ellipse1>() );
    e->draw();

    return 0;
}


