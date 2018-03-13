[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2018a) > T1

TOP500 & me: Comparativo de Arquiteturas Paralelas
--------------------------------------------------

Nome: Carla de Oliveira Barden

| Característica                                            | Computador no TOP500  | Meu computador  |
| --------------------------------------------------------- | --------------------- | --------------- |
| Nome/Título                                               |        Endeavor       |Acer V5 572G 6679 (com HW modificado)|
| Imagem (foto, diagrama, screenshot, etc.)                 | <img src="http://www.top500.org/static//images/Top500_logo.png" width="48"> | <img src="https://images-na.ssl-images-amazon.com/images/I/91tsiX8W3kL._SL1500_.jpg" width="48">|
| Classificação de Flynn                                    |       SIMD/MIMD       |  SIMD/MIMD      |
| Memória: compartilhada, distribuída ou ambas?             |      Ambas            |  Compartilhada  |
| Número total de núcleos de processamento                  |      45,680           |        2        |
| Fabricante e modelo do(s) processador(es)                 |Intel Xeon Phi 7250F   | Intel Core i5-3337U |
| Frequência do(s) processador(es)                          |      1.4GHz           | 1.8GHz          |
| Memória total                                             |      120,640 GB       |        8 GB     |
| Tipo(s) de interconexão entre os núcleos/processadores    |      Intel Omni-Path  |       --        |
| Desempenho Linpack                                        |    1,462.97 TFlop/s   |  2455555.697KFlops/s* |

*Entrada = 1000.

### Referências
- Top 500. Rank 86. https://www.top500.org/system/176908
- Netlib. Linpack. http://www.netlib.org/benchmark/linpackc.new
