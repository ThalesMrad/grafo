#ifndef ENTRADASAIDA
#define ENTRADASAIDA

struct arquivos {
  FILE* entrada;
  FILE* saida;
  int flag;   // flag para poder retornar 0 em caso de erro
}; typedef struct arquivos Arquivos;

Arquivos* argumentosEntrada(int argc, char* argv[]);
int** alocaMatriz(int linha, int coluna);
int verificaArqVazio(FILE* arq);
int calculaQtdArestas(FILE* arq);
int leNumVertices(FILE *arq);
int** leArestas(FILE *arq, int qtdArestas);
void contaTempoProcessador(double *utime, double *stime);
void imprimeTempo(double user_time, double system_time, FILE* arq);
void liberaArquivos(Arquivos *arq);

#endif
