#include <cstdlib>
#include <iostream>
typedef int8_t data_t;

class Container
{
public:
    Container() = default;
    ~Container();
    explicit Container(uint32_t size);
private:
    uint32_t size_;
    data_t* data_;
};

Container::~Container() {
    size_ = 0;
    std::cout << "container destructed\n";
}

Container::Container(uint32_t size):
    size_(size),
    data_(nullptr)
{
    std::cout << "Container constructed with size: " << size_ << std::endl;
}