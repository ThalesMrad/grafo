#ifndef COLORACAO
#define COLORACAO
#include "grafo.h"

typedef struct vertice {
	int id;
	int grauArestas;
  int cor;
  int corDefinitiva;
	int grauSaturacao;
} Vertice;

int verificaCor(int **MatAdj, int *cor, int corAtual, int v, int numVertices);
int coloracaoVertice(int **MatAdj, int *cor, int k, int vertice, int numVertices);
int Backtracking(int **MatAdj, int k, int numVertices);
int AlgoritmoExato(Grafo* gr);

void insertionSort(Vertice* V, int numVertices);
Vertice* inicializaVetorIndice(Grafo* gr);
int heuristica1(Grafo* gr);

int heuristica2(Grafo* gr);
void atualizaSaturacao(Grafo* gr,Vertice* V,int maisSaturado);
int novoMaisSaturado(Grafo* gr,Vertice* V);
void atribuiCor(Grafo* gr,Vertice* V,int maisSaturado);

#endif
