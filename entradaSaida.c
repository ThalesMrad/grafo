#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <math.h>
#include <sys/resource.h>
#include "entradaSaida.h"

Arquivos* argumentosEntrada(int argc, char* argv[]){

  Arquivos* arq = malloc(sizeof(Arquivos));   // armazena os ponteiros dos arquivos
  int opcao;
  arq->flag = 1;                                  // passados por linha de comando em uma struct
  if (argc < 5){
    fprintf(stderr, "Use: ./tp3 -i [ARQUIVO DE ENTRADA DE DADOS] -o [ARQUIVO DE SAIDA]\n");
    arq->flag = 0;
    return arq;
  }
  while((opcao = getopt(argc, argv, "i:o:"))!= -1) { // recebe-se os argumentos por meio
                                                     // da funcao getopt()
    switch(opcao) {
      case 'i':
        if(!(arq->entrada = fopen(optarg, "r"))) {
          fprintf(stderr, "Erro na abertura do arquivo.\n");
          arq->flag = 0;
          return arq;
        }
        break;
      case 'o':
        if(!(arq->saida = fopen(optarg, "w"))) {
          fprintf(stderr, "Erro na abertura do arquivo.\n");
          arq->flag = 0;
          return arq;
        }
    }
  }
  return arq;
}

int** alocaMatriz(int linha, int coluna){

  int **matriz = (int**)calloc(linha,sizeof(int*));
  for (int i=0; i<linha; i++)
    matriz[i] = (int*)calloc(coluna,sizeof(int));

  return matriz;
}

int verificaArqVazio(FILE* arq){
  int tamanho_arq;
  fseek (arq, 0, SEEK_END);               // aponta para o fim do arquivo com fseek()
  if((tamanho_arq = ftell (arq)) == 0){   // retorna o valor da posição do ponteiro com ftell()
    fprintf(stderr, "O arquivo de entrada está vazio!\n");
    return 0;
  }
  rewind(arq);   // retorna o ponteiro para o inicio do arquivo, para os proximos
  return 1;      // procedimentos
}

int calculaQtdArestas(FILE* arq){
  int qtdArestas = 0; // a primeira linha não é uma aresta, por isso -> (-1)
  while (!feof(arq))
    if (fgetc(arq) == '\n')                     // calcula a quantidade de veiculos
      qtdArestas++;                                          // por meio da quantidade de '\n'
  rewind(arq);
  return qtdArestas;
}

int leNumVertices(FILE *arq){
  // int qtdAlgarismo = 0;
  // while (fgetc(arq) != '\n')  // quantidade de algarismos na primeira linha do arquivo
  //   qtdAlgarismo++;           // onde está o número de vertices, para alocar
  // rewind(arq);                // a quantidade certa de memoria para receber o valor
  //
  // char num_char[qtdAlgarismo+1];
  // fgets(num_char, sizeof(num_char), arq); // lê do arq a primeira linha e guarda em num_char
  // int num_int = 0;
  // for (int i = qtdAlgarismo, j = 0; i>0; i--, j++){ // transforma char em int
  //   num_int += (num_char[j]-48) * pow(10, i-1);     // num * 10^i
  // }
int numVertices;
fscanf(arq, "%d",&numVertices);
  return numVertices;
}


int** leArestas(FILE *arq, int qtdArestas){
  int **mat = alocaMatriz(qtdArestas, 2);
  char c;
  for (int i=0; i < qtdArestas; i++){
    for (int j=0; (c = fgetc(arq)) != '\n' && !feof(arq); j++){
        if (j == 0){

          mat[i][0] = c - 48;
          //printf("%d ", mat[i][0]);
        }
        if (j == 2){

          mat[i][1] = c - 48;
          //printf("%d\n", mat[i][1]);
        }

    }
    fscanf(arq, "\n");

  }
  // for (int i=0; i<qtdArestas; i++){
  //   for (int j=0; j<2; j++)
  //   printf("%d ", mat[i][j]);
  //   printf("\n");
  // }
  return mat;
}

void contaTempoProcessador(double *utime, double *stime){
  struct rusage resources;
  getrusage(RUSAGE_SELF, &resources);
  *utime = (double) resources.ru_utime.tv_sec + 1.e-6 * (double) resources.ru_utime.tv_usec;
  *stime = (double) resources.ru_stime.tv_sec + 1.e-6 * (double) resources.ru_stime.tv_usec;
}

void imprimeTempo(double user_time, double system_time, FILE* arq){
  fprintf(arq, "Tempo de execução:\n");
  fprintf(arq, "%fs (tempo de usuário) + %fs (tempo de sistema) = %fs (tempo total)\n\n", user_time, system_time, user_time+system_time);
}

void liberaArquivos(Arquivos *arq){
  fclose(arq->entrada);
  fclose(arq->saida);
  free(arq);
}
