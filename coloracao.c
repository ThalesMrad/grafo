#include <stdio.h>
#include <stdlib.h>
#include "coloracao.h"
#include "grafo.h"

/* Função utilitaria que verifica se a cor atribuida é possível para o vertice.
   Isto é, checa se a aresta existe ou não (MatAdj[v][i] == 1), se existe, então é
   verificado se a cor a ser atribuida ao vertice atual já foi usado por um outro
   vertice adjacente ou não (veticeAtual == cor[i]) */
int verificaCor(int **MatAdj, int *cor, int corAtual, int v, int qtdVertices){

  for(int i=0; i<qtdVertices; i++) // Checando se algum vertice adjacente tem a mesma cor
    if(MatAdj[v][i] && corAtual == cor[i])
      return 0;
  return 1;
}

// Função recursiva que retorna no fim o valor minimo k de cor para dado grafo
int coloracaoVertice(int **MatAdj, int *cor, int k, int vertice, int qtdVertices){

  if(vertice == qtdVertices){
      return 1;
    }  // Caso base: se todos os vertices já estão coloridos

  else {
    // verifica diferente cores para o vertice
    for(int c = 1; c <= k; c++){
      printf("%d ", c);
      //verifica se a cor atual pode ser atribuida ao vertice
      if(verificaCor(MatAdj, cor, c, vertice, qtdVertices)) {
        cor[vertice] = c;
        // recursividade para colorir o restante dos vertices
        if(coloracaoVertice(MatAdj, cor, k, vertice+1, qtdVertices)){
          return 1;
        }

        /*se não for possível construir a árvore de recursividade a partir
          de c, ocorre o "backtracking" removendo o c do vertice (cor[vertice] = 0)*/
        cor[vertice] = 0;
      }
    }
    /* se todas as cores forem verificas e não foi possível colorir todo o gráfico
       então conclui-se que não é possível colorir o grafico com k cores */
    return 0;
  }
}

int Backtracking(Grafo* gr, int k){

  // Vertice* V = inicializaVetorVertice(gr, 0);
  int cor[gr->qtdVertices];

  for(int i=0; i<gr->qtdVertices; i++)
    cor[i]= 0;  // seta a cor de todos os vertices como 0

  // chama coloracaoVertice() a partir do vertice de origem
  return coloracaoVertice(gr->MatAdj, cor, k, 0, gr->qtdVertices);
}

int AlgoritmoExato(Grafo* gr){
  int k = 1;
  while (1){
  if (Backtracking(gr, k))
    break;
  k++;
  }
  return k;
}

void insertionSort(Vertice* V, int qtdVertices){
    int i, j;
    Vertice key;
    for (i = 1; i < qtdVertices; i++){
        key = V[i];
        j = i - 1;
        while (j >= 0 && V[j].grauAresta < key.grauAresta){
            V[j + 1] = V[j];
            j = j - 1;
        }
        V[j + 1] = key;
    }
}

Vertice*  inicializaVetorVertice(Grafo* gr, int caso){
  Vertice* V = malloc(gr->qtdVertices* sizeof(Vertice));
    for(int i = 0; i < gr->qtdVertices; i++){
      V[i].id = i;
      V[i].grauAresta = calculaGrau(gr,i);
      V[i].corDefinitiva = FALSE;
      V[i].cor = 0;
      V[i].grauSaturacao = 0;
    }
    if(caso == 1){
      insertionSort(V, gr->qtdVertices);
    }
    return V;
}

int heuristica1(Grafo* gr){
  /* Primeiro, criamos um vetor de struct Vertice que guarda o número dos vértices
  e o seu respectivo grau. Depois, na função inicializaVetorVertice, salvamos os valores no vetor
  e ordenamos ele com a função insertionSort*/
  Vertice* V = inicializaVetorVertice(gr,1);
  int k = 1;
  for(int i=0; i < gr->qtdVertices; i++){
    V[i].corDefinitiva = TRUE;
    V[i].cor = 1;
    atribuiCor(gr,V,i,1);

    for(int j = 0; j < gr->qtdVertices; j++){
      if(gr->MatAdj[V[i].id][V[i].id] && !V[j].corDefinitiva){
        V[j].cor = V[i].cor ;
      }
    }
    if(V[i].cor > k)
      k = V[i].cor;
  }

  free(V);
  return k;
}
void atribuiCor(Grafo* gr,Vertice* V,int node,int heuristica){
  if(heuristica == 2){
    for(int i = 0; i < gr->qtdVertices; i++){
      if(gr->MatAdj[V[node].id][i] && V[node].cor == V[i].cor){
        V[node].cor++;
        return;
      }
    }
  }else{
    int controle = 0;
    while(V[node].cor > controle){
      for(int j = 0; j < gr->qtdVertices; j++){
        if(gr->MatAdj[V[node].id][V[j].id] && V[node].cor == V[j].cor){
          V[node].cor++;
          break;
        }
      }
      controle++;
    }
  }
  return;
}
int novoMaisSaturado(Grafo* gr,Vertice* V){
  int  maior = -1;
  for(int i=0; i < gr->qtdVertices; i++){
    if(V[i].grauSaturacao > maior && !V[i].corDefinitiva){
      maior = i;
    }
  }
  return maior;
}
void atualizaSaturacao(Grafo* gr,Vertice* V,int maisSaturado){
  for(int i = 0; i < gr->qtdVertices;i++){
    if(gr->MatAdj[i][V[maisSaturado].id])
      V[i].grauSaturacao++;
  }
  return;
}
int heuristica2(Grafo* gr){
  Vertice* V = inicializaVetorVertice(gr, 2);
  int maisSaturado = 0, cor = 0;
  int k = 1;
  for(int i = 0; i < gr->qtdVertices; i++){
    V[maisSaturado].corDefinitiva = TRUE;
    V[maisSaturado].cor = 1;
    int corControle = 0;

    while(corControle < V[maisSaturado].cor){
      printf("%d  ",V[maisSaturado].cor);
      atribuiCor(gr,V,maisSaturado,2);
        corControle++;
      if(corControle > gr->qtdVertices)
        break;
    }
    if(V[maisSaturado].cor > k)
      k = V[maisSaturado].cor;
    atualizaSaturacao(gr,V,maisSaturado);
    maisSaturado = novoMaisSaturado(gr,V);
    }
    free(V);
    return k;
  }
