#include <iostream>
#include "container.hpp"

void test_container();

int main()
{
    std::cout << "Hello!\n";
    test_container();
    return 0;
}


void test_container()
{
    auto cont = new Container[1024];
    Container container(256);
}