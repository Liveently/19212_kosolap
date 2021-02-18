#include "CircularBuffer.h"

typedef char value_type;

CircularBuffer::CircularBuffer() {
    sz = 10;
    buffer = new value_type [sz];
    current = sz-1;
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
        buffer[i] = cb.buffer[i];
    }
}

CircularBuffer::CircularBuffer(int capacity) {
    sz = capacity;
    current = capacity-1;
    buffer = new value_type [sz];
    for (int i = 0; i < sz; i++) buffer[i] = '\0';
}

CircularBuffer::CircularBuffer(int capacity, const value_type &elem) {
    sz = capacity;
    current = sz-1;
    buffer = new value_type [sz];
    for (int i = 0; i < sz; i++) buffer[i] = elem;
}

value_type &CircularBuffer::operator[](int i) {

    int j = (current+1)%sz;

    while (buffer[j] == '\0'){
        j = (j+1)%sz; //нашли первый элемент
    }

    for (int k = 0; k < i; k++){ //идём вперёд на i шагов
        j = (j+1)%sz;
    }

    return buffer[j--];
}

const value_type &CircularBuffer::operator[](int i) const {
    int j = (current+1)%sz;

    while (buffer[j] == '\0'){
        j = (j+1)%sz; //нашли первый элемент
    }

    for (int k = 0; k < i; k++){ //идём вперёд на i шагов
        j = (j+1)%sz;
    }

    return buffer[j--];
}

value_type &CircularBuffer::at(int i) {

    int j = (current+1)%sz;

    while (buffer[j] == '\0'){
        j = (j+1)%sz; //нашли первый элемент
    }

    for (int k = 0; k < i; k++){ //идём вперёд на i шагов
        j = (j+1)%sz;
    }

    if ( (i < 0) || (i >= sz) || (buffer[j] == '\0') ) throw std::out_of_range{"There is no item with this index in the buffer"};
    return buffer[j--];
}

const value_type &CircularBuffer::at(int i) const {
    int j = (current+1)%sz;

    while (buffer[j] == '\0'){
        j = (j+1)%sz; //нашли первый элемент
    }

    for (int k = 0; k < i; k++){ //идём вперёд на i шагов
        j = (j+1)%sz;
    }

    if ( (i < 0) || (i >= sz) || (buffer[j] == '\0') ) throw std::out_of_range{"There is no item with this index in the buffer"};
    return buffer[j--];
}

value_type &CircularBuffer::front() {
    int j = (current+1)%sz;

    while (buffer[j] == '\0'){
        j = (j+1)%sz;
    }

    return buffer[j];
}

value_type &CircularBuffer::back() {
    return buffer[current];
}

const value_type &CircularBuffer::front() const {
    int j = (current+1)%sz;

    while (buffer[j] == '\0'){
        j = (j+1)%sz;
    }

    return buffer[j];
}

const value_type &CircularBuffer::back() const {
    return buffer[current];
}

value_type *CircularBuffer::linearize() {
    auto buff_2 = new value_type [sz]; // создать новый буффер

    int j = (current+1)%sz;

    while (buffer[j] == '\0'){
        j = (j+1)%sz; // первый элемент
    }

    for(int i = 0; i < sz; i++){
        buff_2[i] = buffer[j];
        j = (j+1)%sz;
        if (buff_2[i] != '\0') current = i;
    }

    std::copy(buff_2, buff_2+sz, buffer);

    delete [] buff_2;

    return buffer;
}

bool CircularBuffer::is_linearized() const {

    int j = (current+1)%sz;

    while (buffer[j] == '\0'){
        j = (j+1)%sz; // первый элемент
    }

    return j == 0; //если первый элемент массива на 0 месте
}

void CircularBuffer::rotate(int new_begin) {

    auto buff_2 = new value_type [sz]; // создать новый буффер

    int j = (current+1)%sz;

    while (buffer[j] == '\0'){
        j = (j+1)%sz; // первый элемент
    }

    j = (j+new_begin)%sz; // эл-т, с которого начинаем копировать


    for(int i = 0; i < sz; i++){
        buff_2[i] = buffer[j];
        j = (j+1) %sz;
        if (buff_2[i] != '\0') current = i;
    }

    std::copy(buff_2, buff_2+sz, buffer);

    delete[] buff_2;

}

int CircularBuffer::size() const {
    int count = 0;
    for(int i = 0; i < sz; i++){
        if (buffer[i] != '\0') count++;
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
    if (new_capacity < current) throw std::length_error{"New buffer size is too small"};

    auto buff_2 = new value_type [new_capacity]; // создать новый буффер

    std::copy(buffer, buffer+sz, buff_2);

    sz=new_capacity;
    for(int i = current+1; i < sz; i++){
        buff_2[i] = '\0';
    }

    delete[] buffer;

    buffer = buff_2;
}

void CircularBuffer::resize(int new_size, const value_type &item) {

    linearize();

    if (new_size<current) throw std::length_error{"New buffer size is too small"};

    auto buff_2 = new value_type [new_size]; // создать новый буффер
    std::copy(buffer, buffer+sz, buff_2);

    for(int i = current+1; i < sz; i++){
        buff_2[i] = item;
    }

    delete[] buffer;

    buffer = buff_2;
}

CircularBuffer &CircularBuffer::operator=(const CircularBuffer &cb) {

    if (sz == cb.sz){
        for(int i = 0; i < sz; i++){
            buffer[i] = cb.buffer[i];
        }
        current = cb.current;
        return *this;
    }

    auto buff_2 = new value_type [cb.sz]; // создать новый буффер
    std::copy(cb.buffer, cb.buffer+cb.sz, buff_2);

    delete[] buffer;

    buffer = buff_2;
    sz = cb.sz;
    current = cb.current;
    return *this;
}

void CircularBuffer::swap(CircularBuffer &cb) {

    CircularBuffer tmp;

    tmp=*this;
    *this=cb;
    cb=tmp;

}

void CircularBuffer::push_back(const value_type &item) {
    current=(current+1)%sz;
    buffer[current] = item;
}

void CircularBuffer::push_front(const value_type &item) {

    int j = (current+1)%sz;

    while (buffer[j] == '\0'){
        j = (j+1)%sz;
    }

    buffer[(current+1)%sz] = item;
}

void CircularBuffer::pop_back() {
    buffer[current] = '\0';
    current = (current-1+sz)%sz;
}

void CircularBuffer::pop_front() {

    int j = (current+1)%sz;

    while (buffer[j] == '\0'){
        j = (j+1)%sz;
    }

    buffer[j] = '\0';

}

void CircularBuffer::insert(int pos, const value_type &item) {

    int j = (current+1)%sz;

    while (buffer[j] == '\0'){
        j = (current+1)%sz; //нашли первый элемент
    }

    for (int k = 0; k < pos; j++){ //идём вперёд на i шагов
        j = (current+1)%sz;
    }

    buffer[j] = item;

}

void CircularBuffer::erase(int first, int last) {

    int j = (current+1)%sz;

    while (buffer[j] == '\0'){
        j = (j+1)%sz; //нашли первый элемент
    }

    for (int k = 0; k < first; k++){ //идём вперёд на i шагов
        j = (j+1)%sz;
    }

    for (int k = 0; k < last-1; k++){ //идём вперёд на i шагов
        buffer[j] = '\0';
        j = (j+1)%sz;
    }

}

void CircularBuffer::clear() {
    for(int i = 0; i < sz; i++) buffer[i]='\0';
}


bool operator==(const CircularBuffer & a, const CircularBuffer & b){

    if ( a.sz != b.sz) return false;

    for(int i = 0; i < a.sz ; i++){
        if (a.at(i) != b.at(i)) return false;
    }
    return true;

}

bool operator!=(const CircularBuffer & a, const CircularBuffer & b){
    return !(a == b);
}


