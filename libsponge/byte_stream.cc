#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;
ByteStream::ByteStream(const size_t capacity) {
    // 初始化
    _capacity = capacity; //
    _nread = 0;
    _nwrite = 0;
    _data_buff = vector<char>(_capacity);
    _end_input = false; // 默认打开
}

size_t ByteStream::write(const string &data) {
    size_t cnt = 0;
    for(const auto &item : data){
        if(_nwrite >= _nread + _capacity){
            break;
        }
        _data_buff[_nwrite % _capacity] = item;
        _nwrite++;
        cnt++;
    }
    return cnt;
}

//! \param[in] len bytes will be copied from the output side of the buffer
// 说白了就是将缓冲区里面的len字节读取(复制)出来
string ByteStream::peek_output(const size_t len) const {
    string cnt = string();
    for(size_t i = _nread; (i < _nread + len) && (i < _nwrite); i++){
        cnt.push_back(_data_buff[i % _capacity]);
    }
    return cnt;
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    for(size_t i = 0; i < len; i++){
        if(_nread < _nwrite){
            ++_nread;
        }else{
            return;
        }
    }
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    string s = peek_output(len); // 复制出来的s
    pop_output(s.length());  // 将s从全部pop掉
    return s;
}

void ByteStream::end_input() {_end_input = true;}

bool ByteStream::input_ended() const { return _end_input; }

size_t ByteStream::buffer_size() const { return _nwrite - _nread; }

bool ByteStream::buffer_empty() const { return buffer_size() == 0; }

bool ByteStream::eof() const { return input_ended() && buffer_empty();}

size_t ByteStream::bytes_written() const { return _nwrite; }

size_t ByteStream::bytes_read() const { return _nread; }

size_t ByteStream::remaining_capacity() const { return _capacity - (_nwrite - _nread); }
