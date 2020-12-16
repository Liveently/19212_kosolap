
#ifndef HASH4_HASHTABLE_H
#define HASH4_HASHTABLE_H

#endif //HASH4_HASHTABLE_H
#include <iostream>
#include <string>
#include <utility>

typedef std::string Key;


class Value{
public:
    int age;
    int weight;
};

class Students {

public:
    Value my_value{};
    Key k;
    Students *next; // При возникновении коллизии элементы будут помещены в односвязный список.

    Students (Value &a, Key key){
        my_value = a;
        k=std::move(key);
        next = nullptr;
    }
};


class HashTable {

    Students **table;
    size_t sz;
    size_t elem_num;

    unsigned int hash(const Key &k) { //вычисление хэша

        unsigned int hash_sum = 0;

        for (int i = 0; k[i]; i++)
            hash_sum = (hash_sum + k[i]);

        return hash_sum % sz;
    }

public:

    HashTable() {
        sz = 64;
        elem_num = 0;
        table = new Students *[sz];
        for (int i = 0; i < sz; i++) table[i] = nullptr;
    }

    HashTable(const HashTable &b) {

        sz = b.sz;
        elem_num = b.elem_num;
        table = new Students *[sz];

        for (int i = 0; i < sz; i++) table[i] = nullptr;

        for (int i = 0; i < sz; i++) {

            if (b.table[i] != nullptr) {

                table[i] = new Students(b.table[i]->my_value, b.table[i]->k);
                auto place = table[i];
                auto place_b = b.table[i];
                while (place_b -> next != nullptr) {
                         place->next = new Students(place_b->my_value, place_b->k);
                         place=place->next;
                         place_b = place_b->next;
                }

            }

        };

    }

    ~HashTable() {
        delete[] table;
    }


    bool insert(const Key &k, Value &v) {

        ++elem_num;

  /*      if (elem_num == sz) {

            sz = sz * 2;
            auto n_table = new Students *[sz]; // создать новую табл с size*=2;

            for (int i = 0; table[i]; i++) {

                auto place_a = n_table[i];
                auto place = table[i];

                if (table[i] != nullptr) {

                    table[hash(k)] = new Students(table[i]->my_value, table[i]->k);
                    auto place = table[i];
                    auto place_b = b.table[i];
                    while (place_b->next != nullptr) {
                        place->next = new Students(place_b->my_value, place_b->k);
                        place = place->next;
                        place_b = place_b->next;
                    }


                    while (place->next != nullptr) {
                        place_a = place;
                        place_a = place_a->next;
                        place = place->next;
                    };
                }
                //перенести туда

                delete[] table;

                table = n_table;

            }
        }*/
        unsigned int hashNumber = hash(k);

        Students *place = table[hashNumber];
        if (place == nullptr) {
            table[hashNumber] = new Students(v, k);
            return true;
        }

        while (place->next != nullptr) {
            place = place->next;
        }
        place->next = new Students(v, k);
        return true;

    }// Вставка в контейнер. Возвращаемое значение - успешность вставки.

    bool contains(const Key &k) {

        Students *place = table[hash(k)];

        while (place != nullptr) {
            if (place->k == k) return true;
            place = place->next;
        }
        return false;

    }// Проверка наличия значения по заданному ключу


    size_t size() const {
        return elem_num;
    }


    void clear() {

        elem_num=0;
        for (int i = 0; i < sz; i++) {
            Students *place = table[i];
            table[i] = nullptr;
            if (place != nullptr) {
                auto place_cur = place;
                place->next = nullptr;
                place = place_cur->next;
            }
        }

    }// Очищает контейнер.


    void swap(HashTable &b) { //рассмотреть случай разных длин

        auto x = sz;
        sz = b.sz;
        b.sz = x;

        x = elem_num;
        elem_num = b.elem_num;
        b.elem_num = x;

        Students *tmp[sz];


        for (auto &i : tmp) { i = nullptr; }

        for (int i = 0; i < sz; i++) {

            while (b.table[i] != nullptr) {
                tmp[i] = b.table[i];
                b.table[i] = b.table[i]->next;
            };


            while (table[i] != nullptr) {
                b.table[i] = table[i];
                table[i] = table[i]->next;
            };


            while (tmp[i] != nullptr) {
                table[i] = tmp[i];
                tmp[i] = tmp[i]->next;
            };

        }
    }

    bool empty() const {
        return (size() == 0);
    }


    /*bool erase(const Key& k){

        if(table[hash(k)]!= nullptr) {
            if(table[hash(k)]->k==k)
             delete table[hash(k)];
             table[hash(k)] = nullptr;


            Students *place = table[hash(k)];


            while(place!= nullptr){
                if (place->k == k ) return true;
                place=place->next;
            }
            return false;

        }
        return false;
    }// Удаляет элемент по заданному ключу
*/

    Value &at(const Key &k) {
        Students *place = table[hash(k)];

        while (place != nullptr) {
            if (place->k == k) return place->my_value;
            place = place->next;
        }
    }// Возвращает значение по ключу

    HashTable &operator=(const HashTable &b) {

        clear();

        for (int i = 0; i < sz; i++) {
            table[i] = b.table[i];

            auto place_b = b.table[i];

            while (place_b != nullptr) {
                table[i] = place_b;
                place_b = place_b->next;
                table[i] = table[i]->next;
            };
        }
    }


    Value& operator[](const Key& k){
        return at(k);
    }


    friend bool operator==(const HashTable& a, const HashTable& b){
        if ((a.sz!=b.sz) || (a.elem_num != b.elem_num)) return false;

        for(int i = 0; i<a.sz; i++){

            auto place_a = a.table[i];
            auto place_b = b.table[i];

            while((place_a!= nullptr) && (place_b!= nullptr)){
                if((place_a->k != place_b->k) || (place_a->my_value.weight != place_b->my_value.weight) || (place_a->my_value.age != place_b->my_value.age )) return false;
                place_a=place_a->next;
                place_b=place_b->next;
            };
        }

        return true;
    }


    friend bool operator!=(const HashTable& a, const HashTable& b){
        return (!(a==b));
    }



};
