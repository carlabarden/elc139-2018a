#include <omp.h>
#include <iostream>
#include <string>
#include <algorithm>
#define TAM_ARRAY 1000
#define NTHREADS 5

class SharedArray {
private:
   char* array;
   int index;
   int size;
   
public:
   SharedArray(int n) : size(n), index(0){
      array = new char[size];
      std::fill(array, array+size, '-');
   }
   ~SharedArray() {
      delete[] array;
   }
   
   void addChar(char c, bool error) {
      if (!error){
         #pragma omp critical (insert_char)
         {
            array[index] = c;
            index++;
         }
         spendSomeTime();
      }
       else {
         array[index] = c;
         spendSomeTime();
         index++;
      }
   }
   
   int countOccurrences(char c) {
      return std::count(array, array+size, c);
   }
   
   std::string toString() {
      return std::string(array, size);
   }
   
private:
   void spendSomeTime() {
      for (int i = 0; i < 10000; i++) {
         for (int j = 0; j < 1000; j++) {
         }
      }
   }
};


class ArrayFiller {
private:
   SharedArray* array;
public:
   ArrayFiller() {
      array = new SharedArray(TAM_ARRAY);
   }
   
   void fillArrayConcurrentlyStatic() {
      int i = 0;
      #pragma omp parallel private (i) num_threads(NTHREADS)
      {
         #pragma omp for schedule(static) 
         for (i = 0; i < TAM_ARRAY; i++)
            array->addChar('A'+ omp_get_thread_num(), false);
      }
   }
   
   void fillArrayConcurrentlyDynamic() {
      int i = 0;
      #pragma omp parallel private (i) num_threads(NTHREADS)
      {
         #pragma omp for schedule(dynamic) 
         for (i = 0; i < TAM_ARRAY; i++)
            array->addChar('A'+ omp_get_thread_num(), false);
      }
   }
   
   void fillArrayConcurrentlyError() {
      int i = 0;
      #pragma omp parallel private (i)
      {
         #pragma omp for
         for (i = 0; i < TAM_ARRAY; i++)
            array->addChar('A'+ omp_get_thread_num(), true);
      }
   }
   
   void printStats() {
      std::cout << array->toString() << std::endl;
      for (int i = 0; i < NTHREADS; ++i)
         std::cout << (char) ('A'+i) << "=" 
                   << array->countOccurrences('A'+i) << " ";
      std::cout << std::endl;
      std::cout << "Total de acertos=" 
                   << (TAM_ARRAY - array->countOccurrences('-'));
      std::cout << std::endl;
   }
   ~ArrayFiller() {
      delete array;
   }
};


int main() {
   omp_set_num_threads(NTHREADS);
   std::cout << "Static:" << std::endl;
   ArrayFiller vet1;
   vet1.fillArrayConcurrentlyStatic();
   vet1.printStats();
   std::cout << std::endl;
   
   std::cout << "Dynamic:" << std::endl;
   ArrayFiller vet2;
   vet2.fillArrayConcurrentlyDynamic();
   vet2.printStats();
   std::cout << std::endl;
   
   std::cout << "Sem exclusao mutua:" << std::endl;
   ArrayFiller vet3;
   vet3.fillArrayConcurrentlyError();
   vet3.printStats();
   std::cout << std::endl;
}
