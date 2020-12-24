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
    auto cont = new cnt::Container(128);
    cnt::Container container(256);
    for(int i = 0; i < 10; ++i)
    {
        cnt::Container c(256);
    }
}