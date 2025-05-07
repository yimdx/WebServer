// #ifndef _BUFFER_H_
// #define _BUFFER__H_
// #endif

# pragma once

#include <string>
#include <vector>

namespace webs{

class Buffer
{
public:
    Buffer(size_t init_size = 2048);
    ~Buffer() = default;

    void append(const char* data, size_t len);
    void retrieve(size_t len);
    const char* peek();

    size_t writable();
    size_t readable();

private:

    // helper function
    char* begin();
    void ensure_writable(size_t len);

    std::vector<char> _buffer;
    size_t _read_pos;
    size_t _write_pos;
};

}; // webs