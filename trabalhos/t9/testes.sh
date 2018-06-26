#Por: Carla de Oliveira Barden
#!/bin/bash

N_EXEC=5                   #n de execucoes, para calcular media
touch times.txt            #tempos de cada execução

#execução
function exec(){
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

#sequencial
exec 'original/mandelbrot' 'original/mandelbrot.in' 'Sequencial'
#paralelo openmp
exec 'openmp2/mandelbrot' 'openmp2/mandelbrot.in' 'Paralelo 2 threads'
exec 'openmp4/mandelbrot' 'openmp4/mandelbrot.in' 'Paralelo 4 threads'
exec 'openmp5/mandelbrot' 'openmp5/mandelbrot.in' 'Paralelo 5 threads'
