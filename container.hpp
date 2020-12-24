#include <cstdlib>
#include <iostream>
namespace cnt {

    typedef int8_t data_t;
    static const char* filename = "buffer.txt";
    enum { SIZE = 1 << 12};

    class Container {
    public:
        Container() = delete;

        ~Container();

        explicit Container(uint32_t size);

    private:
        uint32_t size_;
        data_t *data_;
        FILE* fout_;
    };

    Container::~Container() {
        size_ = 0;
        if(fclose(fout_))
            std::cerr << "Close failed!\n";
        std::cout << "container destructed\n";
    }

    Container::Container(uint32_t size) :
            size_(size),
            data_(nullptr),
            fout_(nullptr)
    {
        std::cout << "Container constructed with size: " << size_ << std::endl;
        fout_ = fopen(filename, "rw");
        if(fout_ == nullptr)
        {
            std::cerr << "Open failed!\n";
        }
        try {
            data_ = new data_t[SIZE];
        } catch (const std::bad_alloc& e) {
            std::cerr << e.what() << std::endl;
        }
    }
}