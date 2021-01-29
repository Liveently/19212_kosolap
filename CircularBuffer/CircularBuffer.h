#ifndef CIRCULARBUFFER_CIRCULARBUFFER_H
#define CIRCULARBUFFER_CIRCULARBUFFER_H


typedef char value_type;

class CircularBuffer {

    value_type * buffer;
    size_t sz;
    int current;
public:
    CircularBuffer();
    ~CircularBuffer();
    CircularBuffer(const CircularBuffer & cb);


    explicit CircularBuffer(int capacity); //Конструирует буфер заданной ёмкости.

    CircularBuffer(int capacity, const value_type & elem); //Конструирует буфер заданной ёмкости, целиком заполняет его элементом elem.


    value_type & operator[](int i); //Доступ по индексу. Не проверяют правильность индекса.
    const value_type & operator[](int i) const;


    value_type & at(int i); //Доступ по индексу. Методы бросают исключение в случае неверного индекса.
    const value_type & at(int i) const;

    value_type & front(); //Ссылка на первый элемент.
    value_type & back();  //Ссылка на последний элемент.
    const value_type & front() const;
    const value_type & back() const;

    //Линеаризация - сдвинуть кольцевой буфер так, что его первый элемент
    //переместится в начало аллоцированной памяти. Возвращает указатель
    //на первый элемент.

    value_type * linearize();

    bool is_linearized() const; //Проверяет, является ли буфер линеаризованным.

    void rotate(int new_begin);//Сдвигает буфер так, что по нулевому индексу окажется элемент с индексом new_begin.


    int size() const; //Количество элементов, хранящихся в буфере.
    bool empty() const;

    bool full() const; //true, если size() == capacity().

    int reserve() const; //Количество свободных ячеек в буфере.

    int capacity() const; //ёмкость буфера

    void set_capacity(int new_capacity);//Изменяет размер буфера.


    void resize(int new_size, const value_type & item = value_type()); //В случае расширения, новые элементы заполняются элементом item.

    CircularBuffer & operator=(const CircularBuffer & cb); //Оператор присваивания.

    void swap(CircularBuffer & cb); //Обменивает содержимое буфера с буфером cb.


    void push_back(const value_type & item = value_type()); //Добавляет элемент в конец буфера. Если текущий размер буфера равен его ёмкости, то переписывается первый элемент буфера (т.е., буфер закольцован).


    void push_front(const value_type & item = value_type()); //Добавляет новый элемент перед первым элементом буфера. Аналогично push_back, может переписать последний элемент буфера.

    void pop_back(); //удаляет последний элемент буфера.

    void pop_front(); //удаляет первый элемент буфера.


    void insert(int pos, const value_type & item = value_type()); //Вставляет элемент item по индексу pos. Ёмкость буфера остается неизменной.

    void erase(int first, int last); //Удаляет элементы из буфера в интервале [first, last).

    void clear(); //Очищает буфер
};

bool operator==(const CircularBuffer & a, const CircularBuffer & b);
bool operator!=(const CircularBuffer & a, const CircularBuffer & b);

#endif //CIRCULARBUFFER_CIRCULARBUFFER_H

