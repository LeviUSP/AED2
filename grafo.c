#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

#define MAX 100

typedef struct adj{
    int numeroDoVertice;
    struct adj* prox;
}NO;

typedef struct vertice{

    char cor; //b é branco, c é cinza e p é preto
    int ordem;
    int min;
    int pai;
    
    NO* cab;
}VERTICE;

typedef struct{
    int vertices;
    VERTICE A[MAX+1];//array de vertices
}GRAFO;

GRAFO* criarGrafo(int numerodeVertices){
    GRAFO* gr = (GRAFO*) malloc(sizeof(GRAFO));
    gr->vertices = numerodeVertices;

    return gr;
}

void adicionarAdjacencia(GRAFO* g, int indice, int numeroDoNO){
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->numeroDoVertice = numeroDoNO;
    novo->prox = NULL;

    NO* p = g->A[indice].cab;

    while(p->prox) p = p->prox;

    if (p) p->prox = novo;
    else g->A[indice].cab = novo;
    
}

void adicionarAresta(GRAFO* g, int v, int u){
    adicionarAdjacencia(g, v, u);
    adicionarAdjacencia(g, u, v);
}


void DFS(VERTICE* vertice, int v, int* contador){
    vertice[v].min = vertice[v].ordem;
    NO* p = vertice[v].cab;
    
    while(p){
        int u = p->numeroDoVertice;
        if(vertice[u].cor == -1){

            vertice[u].cor = 'c';
            vertice[u].pai = v;
            vertice[u].ordem = ++(*contador);
            
            DFS(vertice, u, contador);
        };

        if (vertice[v].min > vertice[u].min && u != vertice[v].pai) 
            vertice[v].min = vertice[u].min;

        p = p->prox;
    }
    vertice[v].cor = 'p';
};



bool ehBiconexo(GRAFO* g, char* arestaCritica, int* arestas){
    int vertices = g->vertices;
    int contador = 1;


    VERTICE* vertice = g->A;

    //resetar grafo
    for(int i = 1; i <= g->vertices; i++){
        VERTICE atual = vertice[i];
        
        atual.cor = 'b';
        atual.pai = 0;
        atual.min = 0;
        atual.ordem = 0;
    }


    int v = 1;
    vertice[v].cor = 'c';
    vertice[v].ordem = contador; 

    DFS(vertice, v, &contador);
    
    vertice[v].cor = 'p';

    if (contador < vertices){ 
        printf ("NAO EH CONEXO");
        return false;
    };

    *arestas = 0;
    //o primeiro elemento sempre terá o minimo e ordem iguais
    for (int i = 2; i <= vertices; i++){
        if (vertice[i].min >= vertice[i].ordem){
            arestaCritica[*arestas] = i + '-' + vertice[i].pai;
            (*arestas)++;
        }; 
    }

    return true;
};


int main(){
    GRAFO* gr = criarGrafo(12);
    adicionarAresta(gr, 1, 2);
    adicionarAresta(gr, 1, 3);
    adicionarAresta(gr, 2, 4);
    adicionarAresta(gr, 2, 5);
    adicionarAresta(gr, 3, 5);
    adicionarAresta(gr, 5, 6);
    adicionarAresta(gr, 4, 6);
    adicionarAresta(gr, 4, 7);
    adicionarAresta(gr, 7, 8);
    adicionarAresta(gr, 7, 9);
    adicionarAresta(gr, 7, 12);
    adicionarAresta(gr, 8, 9);
    adicionarAresta(gr, 9, 10);
    adicionarAresta(gr, 9, 11);
    adicionarAresta(gr, 10, 11);
    adicionarAresta(gr, 10, 12);

    char arestaCritica[MAX];
    int qntdeDeArestasCriticas;

    if(ehBiconexo(gr, arestaCritica, &qntdeDeArestasCriticas)) {
        printf ("EH BICONEXO");
        printf ("As  arestas críticas são:");
        for (int i = 0; i < qntdeDeArestasCriticas; i++)
            printf(arestaCritica[i]);
    }
    

    return 0;
}
