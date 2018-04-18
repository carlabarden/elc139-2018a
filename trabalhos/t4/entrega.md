## Scheduling com OpenMP  
**Nome:** Carla de Oliveira Barden  
**Disciplina:** ELC139 - Programação Paralela  

---
### Comentários  
   Neste trabalho, [este](https://github.com/AndreaInfUFSM/elc139-2018a/blob/master/trabalhos/t4/ThreadDemoABC.cpp) código, que usa POSIX Threads, foi modificado para usar Open MP e demonstrar a diferença de resultados ao se utilizar a cláusula `schedule` com a opção `static` ou `dynamic` para o balanceamento da carga do loop.
   O [programa]() modificado mostra na [saída]() como cada array ficou após ser alterado pelas threads em cada caso, bem como o número de acertos (que deve ser igual ao tamanho do array, exceto onde não há exclusão mútua) e a carga de trabalho de cada thread.

---
### Referências  
1. [Linguagem C++](http://www.cplusplus.com/reference/)
2. [Introdução ao Open MP](https://www.ibm.com/developerworks/br/aix/library/au-aix-openmp-framework/index.html)
3. [OpenMP Scheduling](http://cs.umw.edu/~finlayson/class/fall16/cpsc425/notes/12-scheduling.html)
4. [What's the difference between “static” and “dynamic” schedule in OpenMP?](https://stackoverflow.com/questions/10850155/whats-the-difference-between-static-and-dynamic-schedule-in-openmp)
