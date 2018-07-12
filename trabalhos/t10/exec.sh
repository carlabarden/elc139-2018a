#Por: Carla de Oliveira Barden
#!/bin/bash

N_EXEC=5                   #n de execucoes, para calcular media
touch times.txt            #tempos de cada execução

#execução mandelbrot
function execm(){
   PATH=$1
   INPUT=$2
   TYPE=$3
   
   echo -e $TYPE >> times.txt
   
   for ((aux = 0; aux < N_EXEC; aux++))
   do
      echo -e "Execucao $aux" >> times.txt
      ./$PATH < $INPUT >> times.txt
      
   done
   echo -e "\n\n" >> times.txt
}

#execução dotprod
function execd(){
   PATH=$1
   TAMV=$2
   REPT=$3
   TYPE=$4
   
   echo -e $TYPE >> times.txt
   
   for ((aux = 0; aux < N_EXEC; aux++))
   do
      echo -e "Execucao $aux" >> times.txt
      ./$PATH $TAMV $REPT >> times.txt
      
   done
   echo -e "\n\n" >> times.txt
}

#paralelo tbb
execm 'mandelbrot/mandelbrot' 'mandelbrot/mandelbrot.in' 'Mandelbrot 4 threads TBB;'
#dotprod sequencial
execd 'dotprod/dotprodseq' 5000000 1000 'Dotprod sequencial;'
#dotprod paralelo tbb 4 threads
execd 'dotprod/dotprod' 5000000 1000 'Dotprod 4 threads TBB'
echo -e "Done"





