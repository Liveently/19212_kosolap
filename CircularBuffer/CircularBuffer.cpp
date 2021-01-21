#include "CircularBuffer.h"

typedef char value_type;

CircularBuffer::CircularBuffer() {
    sz = 10;
    buffer = new value_type [sz];
    current = 0;
    for (int i = 0; i < sz; i++) buffer[i] = '\0';
}

CircularBuffer::~CircularBuffer() {
    delete[] buffer;
}

CircularBuffer::CircularBuffer(const CircularBuffer &cb) {
    sz = cb.sz;
    current = cb.current;
    buffer = new value_type [sz];

    for (int i = 0; i < sz; i++) {
        buffer[i]=cb.buffer[i];
    };
}

CircularBuffer::CircularBuffer(int capacity) {
    sz = capacity;
    current = 0;
    buffer = new value_type [sz];
    for (int i = 0; i < sz; i++) buffer[i] = '\0';
}

CircularBuffer::CircularBuffer(int capacity, const value_type &elem) {
    sz = capacity;
    current = 0;
    buffer = new value_type [sz];
    for (int i = 0; i < sz; i++) buffer[i] = elem;
}

value_type &CircularBuffer::operator[](int i) {
    return buffer[(current + i)%sz];
}

const value_type &CircularBuffer::operator[](int i) const {
    return buffer[i];
}

value_type &CircularBuffer::at(int i) {
    if(i<0 || i>=sz) throw;
    return buffer[i];
}

const value_type &CircularBuffer::at(int i) const {
    if(i<0 || i>sz) throw;
    return buffer[i];
}

value_type &CircularBuffer::front() {
    return buffer[0];
}

value_type &CircularBuffer::back() {
    return buffer[current];
}

const value_type &CircularBuffer::front() const {
    return buffer[0];
}

const value_type &CircularBuffer::back() const {
    return buffer[current];
}

value_type *CircularBuffer::linearize() {
    auto buff_2 = new value_type [sz]; // создать новый буффер

    for(int i=0; i<sz; i++){
        buff_2[i]=buffer[(current++)%sz];
    }

    std::copy(buff_2, buff_2+sz, buffer);
    current=0;

    delete [] buff_2;

    return buffer;
}

bool CircularBuffer::is_linearized() const {
    if ((buffer[current+1] == '\0') && (buffer[0] != '\0')) return true;
    return false;
}

void CircularBuffer::rotate(int new_begin) {

    auto buff_2 = new value_type [sz]; // создать новый буффер

    for(int i=0; i<sz; i++){
        buff_2[i]=buffer[(new_begin)%sz];
    }

    std::copy(buff_2, buff_2+sz, buffer);
    current=0;

    delete [] buff_2;
}

int CircularBuffer::size() const {
    int count=0;
    for(int i=0; i<sz; i++){
        if (buffer[i]!='\0') count++;
    }
    return count;
}

bool CircularBuffer::empty() const {
    return (size() == 0);
}

bool CircularBuffer::full() const {
    return (size() == sz);
}

int CircularBuffer::reserve() const {
    return (sz - size());
}

int CircularBuffer::capacity() const {
    return sz;
}

void CircularBuffer::set_capacity(int new_capacity) {
    linearize();
    auto buff_2 = new value_type [new_capacity]; // создать новый буффер
    std::copy(buffer, buffer+sz, buff_2);

    delete[] buffer;

    buffer = buff_2;
}

void CircularBuffer::resize(int new_size, const value_type &item) {

    linearize();
    auto buff_2 = new value_type [new_size]; // создать новый буффер
    std::copy(buffer, buffer+sz, buff_2);

    for(int i=current; i< sz; i++){
        buff_2[i]=item;
    }

    delete[] buffer;

    buffer = buff_2;
}

CircularBuffer &CircularBuffer::operator=(const CircularBuffer &cb) {

    if (sz == cb.sz){
        for(int i=0; i<sz; i++){
            buffer[i]=cb.buffer[i];
        }
        current=cb.current;
        return *this;
    }

    auto buff_2 = new value_type [cb.sz]; // создать новый буффер
    std::copy(cb.buffer, cb.buffer+cb.sz, buff_2);


    delete[] buffer;

    buffer = buff_2;
    sz=cb.sz;
    current=cb.current;
    return *this;
}



