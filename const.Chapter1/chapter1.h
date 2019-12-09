#pragma once
#include <vector>

class Widget
{
public:
    Widget() : m(value), M( std::vector<int>(m) ), myIterator( M.begin() )
    {
    }
    int valueOfm() const { return M.size(); }

private:
    static const int value = 2;
    const int m;
    std::vector<int> M;

    const std::vector<int>::iterator myIterator;
};
