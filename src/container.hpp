#include <cstdlib>
#include <iostream>
#include <stdexcept>

namespace cnt {
    static const char* filename = "buffer.txt";
    enum OFFSETS
    {
        SIZE = 1 << 12, // max data_ size
        TOKEN_NUM = 10, // max block size is TOKEN_NUM * size_ * num_ * sizeof(T)
        PAGE_SIZE = 1024
    };

    template <class T>
    class Counter
    {
    private:
        static int count;
    public:
        Counter()
        {
            count++;
        }
        Counter(const Counter &c)
        {
            count++;
        }
        ~Counter()
        {
            count--;
        }
        static int GetCount() {

            return count;
        }
    };

    template<class T>
    int Counter<T>::count = -1;

    template<typename T>
    class Container : private Counter<Container<T>>{
    public:
        using Counter<Container<T>>::GetCount;

        Container() = delete;
        explicit Container(uint32_t size);
        ~Container();

        T& operator[](uint32_t idx) = delete;
        void    addElem(uint32_t idx, T elem);
        const T getElem(uint32_t idx);

        void save_to_file();
        void load_from_file(uint32_t idx);
        void print_data();
        void print_content();
        void print_file();
        void calculate_token_size();

    private:
        uint32_t memory_limit_; // limit of overall memory used
        uint32_t size_;         // limit of RAM used
        uint32_t remainder_;    // the rest of data (if memory_limit_ % PAGE_SIZE != 0)
        uint32_t pos_;          // disk block position
        int32_t  num_;          // number of objects
        T*       data_;
        FILE*    fout_;
    };

    template<typename T>
    Container<T>::~Container() {
        size_ = 0;
        if(fclose(fout_))
            std::cerr << "Close failed!\n";
        delete[] data_;
    }

    template<typename T>
    Container<T>::Container(uint32_t size) :
            memory_limit_(size),
            size_(0),
            pos_(0),
            num_(0),
            data_(nullptr),
            fout_(nullptr)
    {
        num_ = this->GetCount();
        calculate_token_size();
        fout_ = fopen(filename, "w+r+b");
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
    void Container<T>::calculate_token_size()
    {
        if(memory_limit_ > PAGE_SIZE) {
            size_ = PAGE_SIZE;
            remainder_ = memory_limit_ % PAGE_SIZE;
        }
        else{
            size_ = memory_limit_;
            remainder_ = 0;
        }
    }

    template<typename T>
    void Container<T>::save_to_file()
    {
        uint32_t position = pos_ * sizeof(T) + num_ * size_ * TOKEN_NUM * sizeof(T);

        int ret = fseek(fout_, position, SEEK_SET);
        if(ret != 0)
        {
            std::cerr << "Fseek failed!\n";
            return;
        }

        uint32_t size_to_write = 0;

        // the rest of data remained
        if((pos_ / size_ == memory_limit_ / size_) && (remainder_ != 0))
            size_to_write = remainder_;
        else
            size_to_write = size_;

        fwrite(data_, sizeof(T), size_to_write, fout_);
        if(ferror(fout_))
        {
            std::cerr << "Error writing to file\n";
        }
    }

    template<typename T>
    void Container<T>::load_from_file(uint32_t idx)
    {
        uint32_t position = (idx / size_) * size_ * sizeof(T) + num_ * size_ * TOKEN_NUM * sizeof(T);

        int ret = fseek(fout_, position, SEEK_SET);
        if(ret != 0)
        {
            std::cerr << "Fseek failed!\n";
            return;
        }

        uint32_t size_to_read = 0;

        // the rest of data remained
        if((idx / size_ == memory_limit_ / size_) && (remainder_ != 0))
            size_to_read = remainder_;
        else
            size_to_read = size_;

        // std::cout << "idx: " << idx << ", size_to_read: " << size_to_read << std::endl;
        // this->print_content();

        size_t read_size = fread(data_, sizeof(T), size_to_read, fout_);
        if((read_size != size_to_read) && (read_size != 0))
        {
            std::cerr << "Load from file: Fread failed: " << read_size << ", idx: " << idx << std::endl;

        }
        ret = fseek(fout_, 0, SEEK_SET);
        if(ret != 0)
        {
            std::cerr << "Fseek failed!\n";
            return;
        }
    }

    template<typename T>
    void Container<T>::addElem(uint32_t idx, T elem)
    {
        if(idx >= memory_limit_)
        {
            std::cerr << "addElem failed! Index is out of range\n";
            return;
        }
        if(pos_ / size_ == idx / size_) // the same block, nothing to load
        {
            data_[idx % size_] = elem;
        }
        else
        {
            save_to_file();
            load_from_file(idx);

            data_[idx % size_] = elem;
            pos_ = (idx / size_) * size_;
        }
    }

    template<typename T>
    const T Container<T>::getElem(uint32_t idx)
    {
        if(idx >= memory_limit_)
        {
            std::cerr << "addElem failed! Index is out of range\n";
            return T(EXIT_FAILURE);
        }
        if(pos_ / size_ == idx / size_) // the same block
        {
            return data_[idx % size_];
        }
        else
        {
            save_to_file();
            load_from_file(idx);
            pos_ = (idx / size_) * size_;
            return data_[idx % size_];
        }
    }

    /*
     *  uint32_t memory_limit_; // limit of overall memory used
        uint32_t size_;         // limit of RAM used
        uint32_t remainder_;    // the rest of data (if memory_limit_ % PAGE_SIZE != 0)
        uint32_t pos_;          // disk block position
        int32_t  num_;          // number of objects
        T*       data_;
        FILE*    fout_;
     */

    template<typename T>
    void Container<T>::print_content()
    {
        std::cout << "printing content ...\n";
        std::cout << "memory_limit: " << memory_limit_
                  << "\nsize: " << size_
                  << "\nremainder: " << remainder_
                  << "\npos: " << pos_
                  << "\nnum: " << num_ << std::endl;
    }

    template<typename T>
    void Container<T>::print_data()
    {
        std::cout << "printing data ...\n";
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
}