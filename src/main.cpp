#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <ctime>
#include "container.hpp"

void test_container();
void measure_time_addElem(uint32_t data_size, uint32_t max_size);
void test_array(uint32_t size);
void test_large_memory_limist(int size);

int main()
{
    // test_container();
    test_large_memory_limist(65535);
    test_array(65535);
    // measure_time_addElem(1024, 10 * 1024);
    return 0;
}

void test_add_elem(uint32_t size)
{
    cnt::Container<uint32_t> container(size);
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
        test_add_elem(i);
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        out << i << " " << time_spent << "\n";
    }
    out.close();
}

void test_large_memory_limist(int size)
{
    srand(time(NULL));
    std::vector<float> test_data;
    test_data.reserve(size);
    cnt::Container<float> c(size);

    for(uint32_t i = 0; i < size; ++i)
    {
        float random_val = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / size));
        test_data.push_back(random_val);
        // std::cout << random_val << std::endl;
        c.addElem(i, random_val);
    }

    for(int i = 0; i < size; ++i)
    {
        // std::cout << c.getElem(i) << ", " << test_data[i] << std::endl;
        if(c.getElem(i) != test_data[i])
        {
            std::cerr << "test failed: " << i << ", " << test_data[i] << std::endl;
        }
    }
}

void test_container()
{
    uint32_t container_size = 55;
    cnt::Container<uint32_t> container(container_size);
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

void test_array(uint32_t size)
{
    // create array of objects
    std::vector<cnt::Container<float>> v;
    cnt::Container<float> c0(size);
    cnt::Container<float> c1(size);
    cnt::Container<float> c2(size);
    cnt::Container<float> c3(size);
    cnt::Container<float> c4(size);


    for(uint32_t j = 0; j < size; ++j)
    {
        c0.addElem(j, float(float(j) / size));
    }
    for(uint32_t j = 0; j < size; ++j)
    {
        c1.addElem(j, float(float(j) * 2.0 / size));
    }
    for(uint32_t j = 0; j < size; ++j)
    {
        c2.addElem(j, float(float(j) * 3.0 / size));
    }
    for(uint32_t j = 0; j < size; ++j)
    {
        c3.addElem(j, float(float(j) * 4.0 / size));
    }
    for(uint32_t j = 0; j < size; ++j)
    {
        c4.addElem(j, float(float(j) * 5.0 / size));
    }

    for(uint32_t j = 0; j < size; ++j)
    {
        if(c0.getElem(j) != float(float(j) / size)) {
            std::cerr << "test array failed!\n";
        }
    }

    for(uint32_t j = 0; j < size; ++j)
    {
        if(c1.getElem(j) != float(float(j) * 2.0 / size)) {
            std::cerr << "test array failed!\n";
        }
    }

    for(uint32_t j = 0; j < size; ++j)
    {
        if(c2.getElem(j) != float(float(j) * 3.0 / size)) {
            std::cerr << "test array failed!\n";
        }
    }

    for(uint32_t j = 0; j < size; ++j)
    {
        if(c3.getElem(j) != float(float(j) * 4.0 / size)) {
            std::cerr << "test array failed!\n";
        }
    }

    for(uint32_t j = 0; j < size; ++j)
    {
        if(c4.getElem(j) != float(float(j) * 5.0 / size)) {
            std::cerr << "test array failed!\n";
        }
    }

    float middle_val = 1000.1;

    c0.addElem(size / 2, middle_val);
    c1.addElem(size / 2, middle_val);
    c2.addElem(size / 2, middle_val);
    c3.addElem(size / 2, middle_val);
    c4.addElem(size / 2, middle_val);

    for(uint32_t j = 0; j < size; ++j)
    {
        if(c0.getElem(size / 2) != middle_val) {
            std::cerr << "test array failed!\n";
        }
    }
    for(uint32_t j = 0; j < size; ++j)
    {
        if(c1.getElem(size / 2) != middle_val) {
            std::cerr << "test array failed!\n";
        }
    }
    for(uint32_t j = 0; j < size; ++j)
    {
        if(c2.getElem(size / 2) != middle_val) {
            std::cerr << "test array failed!\n";
        }
    }
    for(uint32_t j = 0; j < size; ++j)
    {
        if(c3.getElem(size / 2) != middle_val) {
            std::cerr << "test array failed!\n";
        }
    }
    for(uint32_t j = 0; j < size; ++j)
    {
        if(c4.getElem(size / 2) != middle_val) {
            std::cerr << "test array failed!\n";
        }
    }
}
