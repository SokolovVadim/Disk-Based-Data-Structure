#include <iostream>
#include <fstream>
#include "container.hpp"

void test_container();
void measure_time_addElem(uint32_t data_size, uint32_t max_size);

int main()
{
    test_container();
    //measure_time_addElem(1024, 10 * 1024);
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

void test_add_elem(uint32_t data_size, uint32_t size)
{
    cnt::Container<uint32_t> container(data_size);
    for(uint32_t i = 0; i < size; ++i)
    {
        container.addElem(i, i);
    }
}

void measure_time_addElem(uint32_t data_size, uint32_t max_size)
{
    std::ofstream out("out.txt");
    for(uint32_t i = data_size; i < max_size; i += 4)
    {
        clock_t begin = clock();
        test_add_elem(data_size, i);
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        out << i << " " << time_spent << "\n";
    }
    out.close();
}

void test_container()
{
    // auto cont = new cnt::Container<int>(10);
    cnt::Container<uint32_t> container(10);
    cnt::Container<uint64_t> c(10);
    for(uint64_t i = 0; i < 11; ++i)
    {
        c.addElem(i, i + 5);
    }

    for(uint32_t i = 0; i < 100; ++i)
    {
        container.addElem(i, i);
    }
    // std::cout << container.getElem(5) << std::endl;
    container.addElem(23, 10000);
    std::cout << "get test:\n";
    for(uint32_t i = 0; i < 30; ++i)
    {
        std::cout << container.getElem(i) << " ";
    }
    std::cout << std::endl;

    container.print_data();
    container.print_file();
    c.print_data();
    c.print_file();

    /*
    container.addElem(11, 11);

    std::cout << container.getElem(1) << std::endl;
    std::cout << container.getElem(12);
    std::cout << container.getElem(11);*/
}
