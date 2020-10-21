#include <iostream>
#include <string>
#define S_SIZE 128


using namespace std;


typedef std::string Key;


class Value{

public:
    Value *next; // При возникновении коллизии элементы будут помещены в односвязный список.
    int age;
    int weight;

    Value (int age, int weight){
        this->weight = weight;
        this->age = age;
        this->next = nullptr;
    }

    ~Value(){
        delete this->next;
        this->next = nullptr;
    }
};


class HashTable{

    Value *table[S_SIZE]{};

    static int hash (const Key& k) { //вычисление хэша
        int hash_sum =0;

        for (int i = 0; k[i]; i++)
            hash_sum= (hash_sum+k[i])%(S_SIZE-1);

        return hash_sum;
    }

public:
    HashTable(){
        for (auto & i : table)
            i = nullptr;
    }

    HashTable(const HashTable& b){
        for(int i = 0; i<S_SIZE; i++){
            table[i]=b.table[i];
        }
    } // конструктор с помощью копирования

    ~HashTable(){
        delete *table; // удаление цепочек
        for(auto & i : table){
            i= nullptr;
        } // зануление всего в таблице
    }


    bool insert(const Key& k,  Value& student){

        int hashNumber = hash(k);

        Value *place = table[hashNumber];
        if ( place == nullptr ){
            table[hashNumber] = &student;
            return true;
        }

        while ( place->next != nullptr ){
            place = place->next;
        }
        place->next = &student;
        return true;
    }// Вставка в контейнер. Возвращаемое значение - успешность вставки.


    bool contains(const Key& k) const{
        return (table[hash(k)] != nullptr);
    }// Проверка наличия значения по заданному ключу


    void clear(){
       for(auto & i : table){
           delete i;
           i = nullptr;
       }
    }// Очищает контейнер.


    size_t size() const{
        int sum = 0;
        for (auto i: table){
            Value *place = i;
            if (place!= nullptr) {
                sum++;
                while (place->next != nullptr) {
                    place = place->next;
                    sum++;
                }
            }
        }
        return sum;
    }


    bool empty() const{
        return (size() == 0);
    }


    void swap(HashTable& b){
        Value* tmp[S_SIZE];
        for(int i=0; i<S_SIZE; i++){
            tmp[i]=b.table[i];
            b.table[i]=table[i];
            table[i]=tmp[i];
        }
    }


    bool erase(const Key& k){
        if(table[hash(k)]!= nullptr) {
             delete table[hash(k)];
             table[hash(k)] = nullptr;
            return true;
        }
        return false;
    }// Удаляет элемент по заданному ключу


    Value& at(const Key& k){
        return *table[hash(k)];
    }// Возвращает значение по ключу


    HashTable& operator=(const HashTable& b){
        for (int i = 0; i<S_SIZE; i++){
            table[i]=b.table[i];
        }
       return *this;
    }


    Value& operator[](const Key& k){
        return *table[hash(k)];
    }


    friend bool operator==(const HashTable& a, const HashTable& b){
        for (int i = 0; i<S_SIZE; i++){
            if (a.table[i]!=b.table[i]) return false;
        }
        return true;
    }


    friend bool operator!=(const HashTable& a, const HashTable& b){
        return (!(a==b));
    }

};




int main() {

    HashTable list_first;


    string key[3];
    int age[3], weight[3];


    // вводим значения для первой hash_table

   /* for (int i = 0; i<3; i++) {
        cin >> key[i] >> age[i] >> weight[i];
    } */ //для ввода вручную


    key[0]="Dasha"; age[0]=40; weight[0]=60;
    key[1]="Misha"; age[1]=25; weight[1]=75;
    key[2]="Anna"; age[2]=15; weight[2]=40;


    Value one(age[0], weight[0]); // создание первой структуры
    list_first.insert(key[0], one); // и добавление её в таблицу по ключу key[0]

    Value two(age[1], weight[1]);
    list_first.insert(key[1], two);

    Value three(age[2], weight[2]);
    list_first.insert(key[2], three);


    HashTable list_second(list_first); //вторая таблица - копия первой


    cout<<list_first.at(key[0]).age<<endl; //проверка фу-ции at (должно вывести age[0])
    cout<<list_second.at(key[0]).weight<<endl; //проверка копирования (должно вывести weight[0])

    cout<<list_first.contains(key[1])<<" "<<list_second.contains(key[2])<<" "<<list_second.contains("hey")<<endl; // проверка contains (должно вывести "1 1 0")


    cout<<list_first.size()<<endl; //проверка size (должно вывести "3")


    HashTable list_third; // создание третьего пустого листа

    cout<<list_first.empty()<<" "<<list_third.empty()<<endl; // проверка empty (должно вывести "0 1")

    Value four(10, 30);
    list_third.insert("Vlad", four); // добавление структуры four в третью таблицу


    cout<<(list_first==list_third)<<" "<<(list_first==list_second)<<"  "<<(list_first!=list_third)<<" "<<(list_first!=list_second)<<endl; // проверка операторов == и != (должно вывести "0 1  1 0")

    list_second.clear();
    cout<<list_second.empty()<<endl; // проверка clear (должно вывести 1)


    cout<<list_first.contains(key[0])<<" "; //проверка erase (должно вывести 1 0)
    list_first.erase(key[0]);
    cout<<list_first.contains(key[0])<<endl;


    cout<<list_first.size()<<" "<<list_third.size()<<"  "; // проверка swap (должно вывести "2 1  1 2")
    list_first.swap(list_third);
    cout<<list_first.size()<<" "<<list_third.size()<<endl;

    cout<<list_first["Vlad"].age<<endl; //проверка оператора [] (должно вывести "10")

    list_second=list_first;
    cout<<list_second["Vlad"].age<<endl; //проверка оператора = (должно вывести "10")



    cout<<four.next<<endl; // в next ничего нет - выведется "0"

    // для проверки коллизий
    cout<<list_second.size()<<" "; // до добавления с таким же ключом - размер 1
    Value five(60, 100);
    list_second.insert("Vlad", five);
    cout<<list_second.at("Vlad").next->age<<" "<<list_second.size()<<endl;// после добавления - размер 2, и можно через next найти например age

    list_second.erase("Vlad");
    cout<<list_second.size()<<" "; // удалятся все с ключом "Vlad" -> размер 0


    cout<<four.next; // в next ничего не должно быть - выведется "0"

    return 0;
}


