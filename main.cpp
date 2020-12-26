#include <iostream>
#include "container.hpp"

void test_container();

int main()
{
    std::cout << "Hello!\n";
    test_container();
    return 0;
}

/*
 *  // create objects with max RAM storage
    Container<int8_t> string(1024);
    Container<float> array(4096);
    // fill objects
    for(int i = 0; i < 10000; ++i)
    {
        string[i] = i;
        array[i]  = i;
    }
    // get some data
    float middle = array[5000];
 */

void test_container()
{
    auto cont = new cnt::Container<int>(10);
    cnt::Container<uint32_t> container(10);
    for(uint32_t i = 0; i < 10; ++i)
    {
        container.addElem(i, i);
    }
    /*for(int i = 0; i < 10; ++i)
    {
        std::cout << container[i] << " ";
    }*/
    std::cout << std::endl;

    container.addElem(10, 10);
    container.addElem(11, 11);
}