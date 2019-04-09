#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <string.h>
#define MAX 20

typedef struct adj{
    int numeroDoVertice;
    struct adj* prox;
}NO;

typedef struct vertice{
    char nomeDoVertice;

    char cor; //b é branco, c é cinza e p é preto
    int ordem;
    int min;
    int pai;
    
    NO* cab;
}VERTICE;

typedef struct{
    int vertices;
    VERTICE* A;//array de vertices
}GRAFO;

void printar(GRAFO* g){
    for(int i = 1; i <= g->vertices; i++){
        printf("Vertice %i: ", i);
        printf(" (Cor: %c, Ordem: %i, Minimo: %i e Pai: %i)\n", 
                    g->A[i].cor, g->A[i].ordem, g->A[i].min, g->A[i].pai);
        NO* p = g->A[i].cab;
        printf("   Adjacências: ");
        while(p){
            printf(" v%c", p->numeroDoVertice);
            p = p->prox;
        }        
        printf("\n\n");
    }
}

GRAFO* alocarGrafo(int numeroDeVertices){
    GRAFO* g = (GRAFO*)malloc(sizeof(GRAFO));
    g->vertices = numeroDeVertices;
    g->A = (VERTICE*)malloc((numeroDeVertices+1)*sizeof(VERTICE));
    
    
    return g;
}
//adiciona um nó na lista ligada do vertice indice
void adicionarAdjacencia(GRAFO* g, int indice, int numeroDoNO){
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->numeroDoVertice = numeroDoNO;
    novo->prox = NULL;

    NO* p = g->A[indice].cab;
    while(p && p->prox) p = p->prox;

    if (p) p->prox = novo;
    else g->A[indice].cab = novo;
    
}
//para adicionar aresta de um grafo não direcionado, precisa de ambas adjacencias
void adicionarAresta(GRAFO* g, int v, int u){    
    adicionarAdjacencia(g, v, u);
    adicionarAdjacencia(g, u, v);
}

void inicializarPropriedadesDoVertice(GRAFO* g, char nomeDoVertice, int indice){
    g->A[indice].nomeDoVertice = nomeDoVertice;
    
    g->A[indice].cab = NULL;
    g->A[indice].cor = '-';
    g->A[indice].min= -1;
    g->A[indice].ordem = -1;
    g->A[indice].pai = -1;
}


void inicializarGrafo() {
    int numeroDeVertices;
    char vertice, adjacencia;

    printf("Informe o número de vértices desse grafo:\n");
    scanf("%i\n", &numeroDeVertices);

    GRAFO* g = alocarGrafo(numeroDeVertices);

  
    
    for(int i = 1; i <= g->vertices; i++){
        scanf("%c|", &vertice);
        
        
        inicializarPropriedadesDoVertice(g, vertice, i);
        
        scanf("%c", &adjacencia);
        adicionarAdjacencia(g, i, adjacencia);
        
        while(adjacencia != '/'){
            scanf("%c", &adjacencia);
            adicionarAdjacencia(g, i, adjacencia);
        }

        
    }
}

int main(){
    inicializarGrafo();

    return 0;
}