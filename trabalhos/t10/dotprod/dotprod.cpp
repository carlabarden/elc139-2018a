//g++ -std=c++11 dotprod.cpp -o d -ltbb
#include <stdio.h>
#include <chrono>
#include "tbb/tbb.h"

using namespace std;

void init_vectors(float* a, float* b, int n)
{
   for (int i = 0; i < n; i++)
   {
      a[i] = 0.5;
      b[i] = 1.0; 
   }
}

float dot_product(float a[], float b[], int n){
   float dp = 0.0;
   for (int i = 0; i < n; i++)
      dp += a[i] * b[i];
    /*dp = tbb::parallel_reduce(
            tbb::blocked_range<int>(0,n),
            0.0f, 
            [&](tbb::blocked_range<int> r, float in) ->float
            {
               for (int i = r.begin(); i != r.end(); ++i)
               in += a[i] * b[i];
               return in;
            },
            std::plus<float>()
         );*/
   return dp;
} 


int main(int argc, char **argv)
{
   int n;
   int repeat;
   float dot;

   if ((argc != 3)) {
      printf("Uso: %s <tamanho dos vetores> <repeticoes>\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   n = atoi(argv[1]);       // tamanho dos vetores
   repeat = atoi(argv[2]);  // numero de repeticoes (variar carga)


   // Cria vetores
   float *a = (float *) malloc(sizeof(float) * n);
   float *b = (float *) malloc(sizeof(float) * n);

   if (a == NULL || b == NULL) {
      printf("Erro de alocacao de memoria\n");
      exit(EXIT_FAILURE);      
   }

   init_vectors(a, b, n);

   //tempooo
   auto start_time = chrono::high_resolution_clock::now();
   tbb::parallel_for(int(0), repeat, [&](int i){  
      dot = dot_product(a, b, n);
   });
   auto end_time = chrono::high_resolution_clock::now();
   long long ttime = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
   //printf("Produto escalar;  %f\n", dot);
   printf("Tempo de calculo(microsegundos);  %lld\n", ttime);

   free((void *) a);
   free((void *) b);

   return EXIT_SUCCESS;
}
