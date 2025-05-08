#include "buffer/buffer.hpp"

namespace webs{

size_t Buffer::readable(){
    return _write_pos - _read_pos;
}

size_t Buffer::writable(){
    return _buffer.size() - _write_pos;
}

void Buffer::append(const char* data, size_t len){
    if(len > writable()){
        ensure_writable(len);
    }
    std::copy(data, data+len, begin()+_write_pos);
}

void Buffer::retrieve(size_t len){
    if(len < readable()){
        _read_pos += len;
    }
    else{
        _read_pos = 0;
        _write_pos = 0;
    }
}

const char* Buffer::peek(){
    return begin() + _read_pos;
}

char* Buffer::begin(){
    return &(*_buffer.begin());
}

void Buffer::ensure_writable(size_t len){
    if(len > _read_pos + writable()){
        _buffer.resize(_buffer.size()+len);
    }else{
        std::copy(begin()+_read_pos, begin()+_write_pos, begin());
        _write_pos -= _read_pos;
        _read_pos = 0;
    }

}

}// webs