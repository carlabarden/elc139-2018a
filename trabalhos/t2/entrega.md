## Trabalhando com Profilers  
**Nome:** Carla de Oliveira Barden  
**Disciplina:** ELC139 - Programação Paralela  

---
### Sumário  
1. [Introdução](#intro)
2. [Pt. I: Trabalhando com o GProf](#pt-i)  
3. [Pt. II: Comparando Profilers](#pt-ii)  
3.1 [Sobre o software usado para executar o profile](#pt-ii-1)  
3.2 [Resultados obtidos](#pt-ii-2)
4. [Referências](#ref)
---
<a name=“intro”></a>
### Introdução 
   Profilers são ferramentas capazes de analisar diversos aspectos de uma aplicação, tais quais:  
   * tempo de execução  
   * recursos de hardware utilizados  
   * chamadas de funções  
   
dentre outros, com o propósito principal de mensurar o desempenho e realizar possíveis otimizações no respectivo software.  

Na 1ª parte deste trabalho, foram realizados diversos experimentos usando [este](https://github.com/AndreaInfUFSM/elc139-2018a/blob/master/trabalhos/t2/dotprod_seq/dotprod_seq.c) código e o GProf para obter o seu perfil de execução.  
Na 2ª parte, os experimentos foram feitos usando outro código, desenvolvido por mim, usando GProf e OProfile para obter o seu perfil de execução.

**Observações**  
* Todos os códigos aqui foram compilados com a opção `no-pie` para a correta obtenção dos valores pelo GProf.  
* Todas as aplicações foram testadas em um ambiente mínimo, com o sistema operacional (Sabayon GNU/Linux) rodando em modo recuperação (ocupando +/- 80MB de memória RAM e 0,7% de uma das threads de processamento) para que a interferência  de aplicações concorrentes fosse a menor possível.  
---
<a name=“pt-i”></a>
###  Parte 1: Trabalhando com o GProf    
Na tabela abaixo, encontram-se alguns dados extraídos de algumas das execuções:    

| Exec |Tamanho Vetor | Iterações | Tempo (µs) |  
|--|--|--| --|  
|1| 50.000 | 10 | 1826 |  
|2|5.000.000| 10 | 173301|  
|3|500.000| 100 | 174954 |  
|4|500.000|10.000| 17326919|  
|5|500.000|100.000| 173559565|  
|6|50.000.000|1000| 1726672|  

*Obs: [Aqui](https://github.com/carlabarden/elc139-2018a/tree/master/trabalhos/t2/pt_i) estão as saídas geradas pelo GProf em cada uma das execuções.*   

Analisando a tabela e as saídas geradas pelo GProf, pode-se notar que, apesar do tamanho do vetor aumentar (e, consequentemente, aumentar um pouco o tempo de execução), as chamadas de funções de cada iteração não se alteram. Assim, torna-se vantajoso paralelizar apenas se o número de iterações (que, conforme a tabela, quando é muito grande reflete muito mais no tempo da aplicação) for muito alto, dividindo-se a execução das iterações entre threads.  


---
<a name=“pt-ii”></a>
### Parte 2: Comparando Profilers
Nesta parte do trabalho, foram usados dois softwares: GProf e OProfile. O motivo da escolha é que o [OProfile é capaz de gerar a sua saída em formato compatível com a saída do GProf](http://oprofile.sourceforge.net/doc/opgprof.html), facilitando a comparação.  

<a name=“pt-ii-1”></a>
#### Sobre o software usado para executar os profiles 
Basicamente, ele funciona como um buscador de palavras em arquivos de texto. Se houver no mesmo diretório do programa um arquivo de nome `naoindexar.txt` , as palavras contidas neste arquivo não serão consideradas para a busca. Ao executar o programa, basta digitar a(s) palavra(s) (separadas por espaço) para verificar se elas existem em algum dos arquivo(s) (os arquivos devem estar no mesmo diretório do programa). Internamente, ele armazena as palavras de todos os arquivos, exceto as que estão no arquivo `naoindexar.txt` (caso houver)  numa TRIE, onde no último nível de cada palavra há um ponteiro para uma lista que armazena o nome do(s) arquivo(s) em que a palavra está e quantidade de vezes em que ela aparece em cada um deles.  

Para os testes, foram realizadas execuções das seguintes formas:  
1. Com três textos, sem o arquivo  `naoindexar.txt`, procurando por 20 palavras diferentes em uma única busca;  
2. Com cinco textos, sem o arquivo  `naoindexar.txt`, procurando por 30 palavras diferentes em uma única busca;  
3. Com sete textos, com o arquivo  `naoindexar.txt`, procurando por 30 palavras diferentes em uma única busca.  

Os textos estão em 5 idiomas diferentes, para aumentar a complexidade da execução. Eles foram gerados através dos sites:  
* [Gerador de Lero Lero](http://www.cafw.ufsm.br/~bruno/disciplinas/desenvolvimento_web/material/lerolero.html)  
* [Lorem ipsum](https://br.lipsum.com/)  
* [Random Text Generator](http://www.randomtextgenerator.com/)  

*Obs: O programa não reconhece caracteres especiais, substituindo-os por `xx`.*  
<a name=“pt-ii-2”></a>
#### Resultados Obtidos  

A instalação dos profilers na distribuição alvo foi extremamente simples, já que eles se encontram no seu repositório padrão. O uso, principalmente do OProfile foi um pouco complicado, principalmente pelo grande leque de ferramentas e opções que o aplicativo oferece.
Neste caso seria vantajoso paralelizar a busca de palavras, já que poderia haver um ganho de desempenho buscando-as simultaneamente.  
* [Resultados gerados pelo GProf](https://github.com/carlabarden/elc139-2018a/tree/master/trabalhos/t2/pt_ii/gprof_results)  
* [Resultados gerados pelo OProfile](https://github.com/carlabarden/elc139-2018a/tree/master/trabalhos/t2/pt_ii/oprofile_results)


---
<a name=“ref”></a>
### Referências  
1. [Sobre opção -no-pie](https://forums.gentoo.org/viewtopic-p-8175568.html?sid=e3551a3fac6545264e8ad3967f86560a)
2. [Análise de Desempenho com GProf](https://www.embarcados.com.br/desempenho-gnu-profiler-gprof/)
3. [Man Oprofile](http://oprofile.sourceforge.net/doc/index.html)
4. [gprof-compatible output](http://oprofile.sourceforge.net/doc/opgprof.html)

