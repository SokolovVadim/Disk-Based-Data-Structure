#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include "container.hpp"

void test_container();
void measure_time_addElem(uint32_t data_size, uint32_t max_size);
void test_array(uint32_t elem_num, uint32_t data_size, uint32_t max_size);
void test_large_memory_limist();

int main()
{
    // test_container();
    test_large_memory_limist();
    // test_array(1, 10, 25);
    // measure_time_addElem(1024, 10 * 1024);
    return 0;
}

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

void test_large_memory_limist()
{
    cnt::Container<uint32_t> c(65535);
    for(uint32_t i = 0; i < 65535; ++i)
    {
        c.addElem(i, i);
    }
    for(uint32_t i = 0; i < 65535; ++i)
    {
        c.getElem(i);
    }
}

void test_container()
{
    cnt::Container<uint32_t> container(55);
    cnt::Container<uint32_t> c(25);
    for(uint32_t i = 0; i < 25; ++i)
    {
        c.addElem(i, i);
    }

    for(uint32_t i = 0; i < 55; ++i)
    {
        container.addElem(i, i);
    }
    // std::cout << container.getElem(5) << std::endl;
    container.addElem(23, 10000);
    std::cout << "get test:\n";
    for(uint32_t i = 0; i < 55; ++i)
    {
        std::cout << container.getElem(i) << " ";
    }
    std::cout << std::endl;

    for(uint32_t i = 0; i < 25; ++i)
    {
        std::cout << c.getElem(i) << " ";
    }
    std::cout << std::endl;


    for(uint32_t i = 0; i < 30; ++i)
    {
        container.addElem(i, i * 2);
    }
    for(uint32_t i = 0; i < 55; ++i)
    {
        std::cout << container.getElem(i) << " ";
    }
    std::cout << std::endl;

    for(uint32_t i = 0; i < 25; ++i)
    {
        c.addElem(i, i * 10);
    }
    for(uint32_t i = 0; i < 25; ++i)
    {
        std::cout << c.getElem(i) << " ";
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

void test_array(uint32_t elem_num, uint32_t data_size, uint32_t max_size)
{
    // create array of objects
    std::vector<cnt::Container<float>> v;
    cnt::Container<float> c0(data_size);
    cnt::Container<float> c1(data_size);
    cnt::Container<float> c2(data_size);
    cnt::Container<float> c3(data_size);
    cnt::Container<float> c4(data_size);


    for(uint32_t j = 0; j < max_size; ++j)
    {
        c0.addElem(j, j);
    }
    for(uint32_t j = 0; j < max_size; ++j)
    {
        c1.addElem(j, j * 2);
    }
    for(uint32_t j = 0; j < max_size; ++j)
    {
        c2.addElem(j, j * 3);
    }
    for(uint32_t j = 0; j < max_size; ++j)
    {
        c3.addElem(j, j * 4);
    }
    for(uint32_t j = 0; j < max_size; ++j)
    {
        c4.addElem(j, j * 5);
    }

    for(uint32_t j = 0; j < max_size; ++j)
    {
        std::cout << c0.getElem(j) << " ";
    }
    std::cout << "\n";

    for(uint32_t j = 0; j < max_size; ++j)
    {
        std::cout << c1.getElem(j) << " ";
    }
    std::cout << "\n";

    for(uint32_t j = 0; j < max_size; ++j)
    {
        std::cout << c2.getElem(j) << " ";
    }
    std::cout << "\n";

    for(uint32_t j = 0; j < max_size; ++j)
    {
        std::cout << c3.getElem(j) << " ";
    }
    std::cout << "\n";

    for(uint32_t j = 0; j < max_size; ++j)
    {
        std::cout << c4.getElem(j) << " ";
    }
    std::cout << "\n";

    c0.addElem(data_size / 2, 10000);
    c1.addElem(data_size / 2, 10000);
    c2.addElem(data_size / 2, 10000);
    c3.addElem(data_size / 2, 10000);
    c4.addElem(data_size / 2, 10000);

    for(uint32_t j = 0; j < max_size; ++j)
    {
        std::cout << c0.getElem(j) << " ";
    }
    std::cout << "\n";

    for(uint32_t j = 0; j < max_size; ++j)
    {
        std::cout << c1.getElem(j) << " ";
    }
    std::cout << "\n";

    for(uint32_t j = 0; j < max_size; ++j)
    {
        std::cout << c2.getElem(j) << " ";
    }
    std::cout << "\n";

    for(uint32_t j = 0; j < max_size; ++j)
    {
        std::cout << c3.getElem(j) << " ";
    }
    std::cout << "\n";

    for(uint32_t j = 0; j < max_size; ++j)
    {
        std::cout << c4.getElem(j) << " ";
    }
    std::cout << "\n";

    /*
    // auto array = new cnt::Container<float>[elem_num];
    for(uint32_t i = 0; i < elem_num; ++i)
    {
       v.push_back(cnt::Container<float>(data_size));

    }
    // iterate over it in order to test multiple objects behavior
    for(uint32_t i = 0; i < elem_num; ++i)
    {
        for(uint32_t j = 0; j < max_size; ++j)
        {
            v[i].addElem(j, i * j);
        }
    }
    // print data
    for(uint32_t i = 0; i < elem_num; ++i)
    {
        for(uint32_t j = 0; j < max_size; ++j)
        {
            std::cout << v[i].getElem(j) << " ";
        }
        std::cout << "\n";
    }
    v.clear();*/
}
