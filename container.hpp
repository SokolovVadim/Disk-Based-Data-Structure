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
        const T getElem(uint32_t idx);
        void save_to_file();
        void load_from_file(uint32_t idx);
        void print_data();
        void print_file();
        void write_to_file(uint32_t pos);
        // uint32_t calculate_position(uint32_t pos);

    private:
        uint32_t size_; // limit of RAM used
        uint32_t pos_;  // disk block
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
        fout_ = fopen(filename, "r+w+b");
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
    void Container<T>::load_from_file(uint32_t idx)
    {
        uint32_t position = (idx / size_) * size_ * sizeof(T);
        std::cout << "position: " << position << std::endl;
        int ret = fseek(fout_, position, SEEK_SET);
        if(ret != 0)
        {
            std::cerr << "Fseek failed!\n";
            return;
        }
        size_t read_size = fread(data_, sizeof(T), size_, fout_);
        if(read_size != size_)
        {
            std::cerr << "Fread failed: " << read_size << std::endl;
        }
        ret = fseek(fout_, 0, SEEK_SET);
        if(ret != 0)
        {
            std::cerr << "Fseek failed!\n";
            return;
        }
        std::cout << "loading from file ...\n";
        for(int i = 0; i < size_; ++i)
            std::cout << data_[i] << " ";
        std::cout << "\n";
    }


    template<typename T>
    void Container<T>::write_to_file(uint32_t pos)
    {
        std::size_t written_size = fwrite(data_, sizeof(T), size_, fout_);
        if(written_size != size_)
        {
            std::cerr << "Fwrite failed: " << written_size << std::endl;
        }
    }

    template<typename T>
    void Container<T>::addElem(uint32_t idx, T elem)
    {
        std::cout << "adding elem ...\n";
        std::cout << "idx: " << idx << std::endl;
        if(idx < size_)
        {
            std::cout << "idx is not out of range\n";
            if(pos_ / size_ == 0) // the same block
            {
                data_[idx] = elem;
                pos_ = 0;
            }
            else
            {
                save_to_file();
                load_from_file(idx);
                data_[idx] = elem;
                pos_ = 0;
            }
        }
        else // out of range
        {
            if(pos_ / size_ == idx / size_) // the same block
            {
                std::cout << "idx > size, the same block, idx: " << idx << std::endl;
                data_[idx % size_] = elem;
            }
            else
            {
                std::cout << "idx > size, different block, idx: " << idx << std::endl;
                print_data();
                save_to_file();
                print_data();
                load_from_file(idx);
                print_data();
                data_[idx % size_] = elem;
                pos_ = (idx / size_) * size_;
                print_data();
            }
        }
        // return data_[idx];

    }

    template<typename T>
    const T Container<T>::getElem(uint32_t idx)
    {
        std::cout << "getting elem ...\n";
        if(idx < size_)
        {
            if(pos_ / size_ == 0) // the same block
            {
                return data_[idx];
            }
            else
            {
                save_to_file();
                load_from_file(idx);
                pos_ = 0;
                return data_[idx];
            }
        }
        else
        {
            std::cout << "idx is out of range\n";
            if(pos_ / size_ == idx / size_) // the same block
            {
                std::cout << "idx > size, the same block, idx: " << idx << std::endl;
                return data_[idx % size_];
            }
            else
            {
                std::cout << "idx > size, different block, idx: " << idx << std::endl;
                save_to_file();
                load_from_file(idx);
                pos_ = (idx / size_) * size_;
                return data_[idx % size_];
            }

        }
    }

    template<typename T>
    void Container<T>::print_data()
    {
        for(int i = 0; i < size_; ++i)
            std::cout << data_[i] << " ";
        std::cout << std::endl;
    }

    template<typename T>
    void Container<T>::print_file()
    {
        std::cout << "printing file ...\n";
        int ret = fseek(fout_, 0L, SEEK_SET);
        if(ret != 0)
        {
            std::cerr << "Fseek failed!\n";
            return;
        }
        ret = fseek(fout_, 0, SEEK_END);
        if(ret != 0)
        {
            std::cerr << "Fseek failed!\n";
            return;
        }
        long int file_size = ftell(fout_);
        if(file_size == -1L)
        {
            std::cerr << "Ftell failed!\n";
            return;
        }
        std::cout << "Size of file: " << file_size << std::endl;

        ret = fseek(fout_, 0L, SEEK_SET);
        if(ret != 0)
        {
            std::cerr << "Fseek failed!\n";
            return;
        }
        if(file_size > SIZE) // read limit
        {
            file_size = SIZE;
        }

        auto buffer = new T[file_size];
        size_t read_size = fread(buffer, sizeof(int8_t), std::size_t(file_size), fout_);
        if(read_size != file_size)
        {
            std::cerr << "Fread failed: " << read_size << std::endl;
        }
        for(int i = 0; i < file_size / sizeof(T); ++i)
        {
            std::cout << buffer[i] << " ";
        }
        std::cout << std::endl;
        delete[] buffer;
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