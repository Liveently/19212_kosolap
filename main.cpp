#include <iostream>

class Array{

public:
      explicit Array(int initial_allocated){ //конструктор - создаёт массив размером initial_allocated
          allocated = initial_allocated;
          mem = new int[allocated];
       }


       Array(){ //конструктор без параметров, делает размер массива заранее заданным, стандартным для класса Array define_size
           allocated = define_size;
           mem = new int[allocated];
       }


      Array(struct Array const &a){ //конструктор копирования
          mem=a.mem;
          allocated=a.allocated;
          size=a.size;
      }


      ~Array(){
          delete [] mem;
      }


      void add_number_to_array(int number){
          if(size == allocated){

              int* tmp =mem;

              mem = new int[allocated*2];

              allocated*=2;
              mem = tmp;
          }

          mem[++size] = number;

      }


      int from_index (int i){  // не понимаю, где нужно использовать ссылки в этой ф-ии
          return mem[i];

      }

      int *mem;
      int allocated;
      int size=0;
      int define_size = 16;
};


void read_array(){
    FILE *f = fopen("input.txt", "r");
    Array a(12);
    int number = 0;
    while (1 == fscanf(f, "%d", &number)){
        a.add_number_to_array(number);
    }
    fclose(f);
}


int main(){
    return 0;
}