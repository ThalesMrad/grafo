#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "coloracao.h"
#include "entradaSaida.h"

int main(int argc, char *argv[]){

  Arquivos* arq = argumentosEntrada(argc, argv);
  if (arq->flag && verificaArqVazio(arq->entrada)){
    int qtdArestas = calculaQtdArestas(arq->entrada);

    Grafo* gr = inicializaGrafo(arq->entrada);

    if (ConstroiGrafo(gr, qtdArestas,arq->entrada)){

      int k;
      double utime_ant, utime_pos, stime_ant, stime_pos;

      contaTempoProcessador(&utime_ant, &stime_ant);
      k = AlgoritmoExato(gr);
      contaTempoProcessador(&utime_pos, &stime_pos);
      imprimeTempo(utime_pos-utime_ant, stime_pos-stime_ant, arq->saida);
      fprintf(arq->saida  , "%d\n", k);


      contaTempoProcessador(&utime_ant, &stime_ant);
      k = heuristica1(gr);
      contaTempoProcessador(&utime_pos, &stime_pos);
      imprimeTempo(utime_pos-utime_ant, stime_pos-stime_ant, arq->saida);
      fprintf(arq->saida  , "%d\n", k);

      contaTempoProcessador(&utime_ant, &stime_ant);
      k = heuristica2(gr);
      contaTempoProcessador(&utime_pos, &stime_pos);
      imprimeTempo(utime_pos-utime_ant, stime_pos-stime_ant, arq->saida);
      fprintf(arq->saida  , "%d\n", k);

    }
    liberaGrafo(gr);
    liberaArquivos(arq);
  }
}
