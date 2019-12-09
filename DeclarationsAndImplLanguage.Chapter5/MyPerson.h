#pragma once
#include <memory>

class MyPersonImpl;
class MyPersonView {

public:
    MyPersonView();
    void audit();

private:
    std::shared_ptr<MyPersonImpl> pImpl;
};
