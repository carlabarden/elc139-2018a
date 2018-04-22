// Simulação de incêndio em uma floresta.
// Baseada no código proposto por David Joiner.
//
// Uso: firesim <tamanho-do-problema> <nro. experimentos> <probab. maxima> 

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "Random.h"
#include "Forest.h"
#include <time.h>
#include <omp.h>

#define NUM_THREADS 4

void
checkCommandLine(int argc, char** argv, int& size, int& trials, int& probs)
{
   if (argc > 1) {
      size = atoi(argv[1]);
   }   
   if (argc > 2) {
      trials = atoi(argv[2]);
   }
   if (argc > 3) {
      probs = atoi(argv[3]);
   }   
}

int 
main(int argc, char* argv[]) 
{
   
   // parâmetros dos experimentos
   int forest_size = 30;
   int n_trials = 5000;
   int n_probs = 101;

   double* percent_burned; // percentuais queimados (saída)
   double* prob_spread;    // probabilidades (entrada)
   double prob_min = 0.0;
   double prob_max = 1.0;
   int base_seed = 100;
   double prob_step;
   checkCommandLine(argc, argv, forest_size, n_trials, n_probs);
    

   try {
   //calcular o tempo
   double starttime = omp_get_wtime();

   // Aloca uma floresta para cada thread
   Forest** forest = (Forest**) malloc(sizeof(Forest*) * NUM_THREADS);
   for(int i = 0; i < NUM_THREADS; i++)
      forest[i] = new Forest(forest_size);

      Random rand;

      prob_spread = new double[n_probs];
      percent_burned = new double[n_probs];

      prob_step = (prob_max - prob_min)/(double)(n_probs-1);
      printf("Probabilidade, Percentual Queimado\n");


      // para cada probabilidade, calcula o percentual de árvores queimadas
      for (int ip = 0; ip < n_probs; ip++) {
         prob_spread[ip] = prob_min + (double) ip * prob_step;
         percent_burned[ip] = 0.0;
         rand.setSeed(base_seed+ip); // nova seqüência de números aleatórios

         // executa vários experimentos
#pragma omp parallel for schedule(static) num_threads(NUM_THREADS) shared(percent_burned, prob_spread, rand)
         for (int it = 0; it < n_trials; it++) {
         int forest_index = omp_get_thread_num();
            // queima floresta até o fogo apagar
            forest[forest_index]->burnUntilOut(forest[forest_index]->centralTree(), prob_spread[ip], rand);
#pragma omp critical
            percent_burned[ip] += forest[forest_index]->getPercentBurned();

}

         // calcula média dos percentuais de árvores queimadas
         percent_burned[ip] /= n_trials;

         // mostra resultado para esta probabilidade
         printf("[%d] %lf, %lf\n",ip, prob_spread[ip], percent_burned[ip]);
      }

   double endtime = omp_get_wtime();
   printf("\nTempo decorrido: %.2f segundos\n", endtime - starttime);
      delete[] prob_spread;
      delete[] percent_burned;
   }
   catch (std::bad_alloc)
   {
      std::cerr << "Erro: alocacao de memoria" << std::endl;
      return 1;
   }

   return 0;
}

