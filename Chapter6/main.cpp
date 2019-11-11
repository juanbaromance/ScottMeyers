// Scott Meyers Chapter 6 on Items 34,43,44

#include <iostream>
#include "main.hpp"

int main()
{
    std::unique_ptr<Shape<Rectangle>> r( std::make_unique<Rectangle>() );
    r->name("MyRectangle");
    r->draw();
    r->dump( ( boost::format("(%08x)") % r->ObjectID() ).str() );

    std::unique_ptr<Ellipse1> e( std::make_unique<Ellipse1>() );
    e->dump( std::to_string( e->valueOfarea() ) );
    for( const auto & i : {1,2} )
        e->draw();

    return 0;
}


