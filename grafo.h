#ifndef GRAFO
#define GRAFO

#define TRUE 1
#define FALSE 0

typedef struct grafo {
	int numVertices;
	int** MatAdj;        // Matriz de adjacencia
	//int* grau;
} Grafo;

Grafo* inicializaGrafo(FILE* arq);
void liberaGrafo(Grafo* gr);
int insereAresta(Grafo* gr, int i, int j);
int ConstroiGrafo(Grafo* gr, int qtdArestas,FILE* arq);
int calculaGrau(Grafo* gr,int i);
void imprimeGrafo(Grafo* gr, FILE* arq);

#endif
