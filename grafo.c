#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "entradaSaida.h"

Grafo* inicializaGrafo(FILE* arq) {
	Grafo* gr = (Grafo*)malloc(sizeof(Grafo));
	gr->numVertices = leNumVertices(arq);
	gr->MatAdj = alocaMatriz(gr->numVertices,gr->numVertices);
	//calculaGrau(gr);
	return gr;
}

void liberaGrafo(Grafo* gr) {
	int i;
	for (i = 0; i < gr->numVertices; i++) {
		free(gr->MatAdj[i]);
	}
	free(gr->MatAdj);
	//free(gr->grau);
	free(gr);
}

int insereAresta(Grafo *gr, int i, int j) {
	if (i >= 0 && i <  gr->numVertices && j >= 0 && j < gr->numVertices) {
		gr->MatAdj[i][j] = TRUE;
		gr->MatAdj[j][i] = TRUE;   // grafo não direcionado
    return 1;
	}
    return 0;
	}


int ConstroiGrafo(Grafo* gr, int qtdArestas,FILE* arq){
	int **mat = leArestas(arq, qtdArestas);
	for (int i=1; i<qtdArestas; i++)
		if (!insereAresta(gr, mat[i][0], mat[i][1])) {
			fprintf(stderr, "Falha na inserção da aresta. Cheque o arquivo de entrada.\n");
			return 0;
		}
	return 1;
}

//
// int verificaAresta(Grafo* gr, int i, int j) {
//
//   if (i >= 0 && i < gr->numVertices && j > 0 && j < gr->numVertices)
// 		return gr->MatAdj[i][j];
//   else
// 		return FALSE;
//
// }


void imprimeGrafo(Grafo* gr, FILE* arq){
  for (int i=0; i< gr->numVertices; i++){
    for (int j=0; j< gr->numVertices; j++){
      printf("%d ", gr->MatAdj[i][j]);
		}
    printf("\n");
  }
}



int calculaGrau(Grafo* gr,int i){
	int grau =0,j;
		for(j = 0; j < gr->numVertices; j++){
			if(gr->MatAdj[i][j])
				grau++;
		}
		return grau;
	}
