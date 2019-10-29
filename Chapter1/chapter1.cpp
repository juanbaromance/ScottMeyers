#include "chapter1.h"
#include <iostream>

const int Widget::value;

int main()
{
    Widget w;
    std::cout << __PRETTY_FUNCTION__ << w.valueOfm() << std::endl;

    return 0;
}


