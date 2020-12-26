#include <cstdlib>
#include <iostream>
#include <stdexcept>
namespace cnt {

    typedef int8_t data_t;
    static const char* filename = "buffer.txt";
    enum { SIZE = 1 << 12};

    template<typename T>
    class Container {
    public:
        Container() = delete;
        explicit Container(uint32_t size);
        ~Container();

        T& operator[](uint32_t idx) = delete;
        void addElem(uint32_t idx, T elem);
        void save_to_file();
        void write_to_file(uint32_t pos);
        // uint32_t calculate_position(uint32_t pos);

    private:
        uint32_t size_; // limit of RAM used
        uint32_t pos_;  // overall position (disk + RAM)
        int32_t offset_; // RAM position
        T *data_;
        FILE* fout_;
    };

    template<typename T>
    Container<T>::~Container() {
        size_ = 0;
        if(fclose(fout_))
            std::cerr << "Close failed!\n";
        std::cout << "container destructed\n";
    }

    template<typename T>
    Container<T>::Container(uint32_t size) :
            size_(size),
            pos_(0),
            offset_(-1),
            data_(nullptr),
            fout_(nullptr)
    {
        std::cout << "Container constructed with size: " << size_ << std::endl;
        fout_ = fopen(filename, "r+w");
        if(fout_ == nullptr)
        {
            std::cerr << "Open failed!\n";
        }
        try {
            data_ = new T[size_];
        } catch (const std::bad_alloc& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    template<typename T>
    void Container<T>::save_to_file()
    {
        fwrite(data_, sizeof(T), size_, fout_);
        if(ferror(fout_))
        {
            std::cerr << "Error writing to file\n";
        }
    }

    template<typename T>
    void Container<T>::write_to_file(uint32_t pos)
    {
        fwrite(data_, sizeof(T), size_, fout_);
        if(ferror(fout_))
        {
            std::cerr << "Error writing to file\n";
        }
    }

    template<typename T>
    void Container<T>::addElem(uint32_t idx, T elem)
    {
        std::cout << "idx: " << idx << " offset: " << offset_ << std::endl;
        if(idx < size_)
        {
            std::cout << "idx is not out of range\n";
            data_[idx] = elem;
            offset_++;
            pos_++;
        }
        else
        {
            if((idx == size_) && (offset_ == size_ - 1)) //
            {
                std::cout << "fulfilled for the first time" << std::endl;
                save_to_file();
                offset_  = 0;
                pos_     = idx;
                data_[0] = elem;
            }
            else
            {
                std::cout << "idx > size, idx: " << idx << std::endl;
                data_[idx % size_] = elem;
            }
        }
        // return data_[idx];

    }

/*    template<typename T>
    uint32_t Container<T>::calculate_position(uint32_t pos)
    {
        if(pos < pos_)
            return pos;
        else
        {

        }
    }*/


}