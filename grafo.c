#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <string.h>

#define MAX 100

typedef struct adj{
    int numeroDoVertice;
    struct adj* prox;
}NO;

typedef struct vertice{
    int numero;
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
        printf("Vertice %i tem adjacencia com", g->A[i].numero);
        NO* p = g->A[i].cab;
        while(p){
            printf(" v%i", p->numeroDoVertice);
            p = p->prox;
        }
        printf("\n    Cor: %c, Ordem: %i, Minimo: %i e Pai: %i", 
                    g->A[i].cor, g->A[i].ordem, g->A[i].min, g->A[i].pai);
        printf("\n\n");
    }
}

GRAFO* criarGrafo(int numerodeVertices){
    
    GRAFO* g = (GRAFO*)malloc(sizeof(GRAFO));
    g->vertices = numerodeVertices;

    g->A = (VERTICE*)malloc((numerodeVertices+1)*sizeof(VERTICE));
    
    for(int i = 1; i <= numerodeVertices; i++){
        g->A[i].numero = i;
        g->A[i].cab = NULL;
        g->A[i].cor = '-';
        g->A[i].min= -1;
        g->A[i].ordem = -1;
        g->A[i].pai = -1;
    }
    return g;
}

void adicionarAdjacencia(GRAFO* g, int indice, int numeroDoNO){
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->numeroDoVertice = numeroDoNO;
    novo->prox = NULL;

    NO* p = g->A[indice].cab;
    
 
    while(p && p->prox) p = p->prox;

    if (p) p->prox = novo;
    else g->A[indice].cab = novo;
    
}

void adicionarAresta(GRAFO* g, int v, int u){
    
    adicionarAdjacencia(g, v, u);
    adicionarAdjacencia(g, u, v);
}


void DFS(GRAFO* g, int v, int* contador){
    g->A[v].min = g->A[v].ordem;
    NO* p = g->A[v].cab;
    

    while(p){
        int u = p->numeroDoVertice;
        if(g->A[u].cor == 'b'){

            g->A[u].cor = 'c';
            g->A[u].pai = v;
            g->A[u].ordem = ++(*contador);
            
            DFS(g, u, contador);
        };

        if (g->A[v].min > g->A[u].min && u != g->A[v].pai) 
            g->A[v].min = g->A[u].min;

        p = p->prox;
    }
    g->A[v].cor = 'p';
};



bool ehBiconexo(GRAFO* g, char arestaCritica[], int* cont){
    int vertices = g->vertices;
    int contador = 1;



    //resetar grafo
    for(int i = 1; i <= g->vertices; i++){
        g->A[i].cor = 'b';
        g->A[i].pai = 0;
        g->A[i].min = 0;
        g->A[i].ordem = 0;
    }


    int v = 1;
    g->A[v].cor = 'c';
    g->A[v].ordem = contador; 

    DFS(g, v, &contador);
    
    g->A[v].cor = 'p';

    if (contador < vertices){ 
        printf ("NAO EH CONEXO\n");
        return false;
    };

    *cont = 0;
    //o primeiro elemento sempre terá o minimo e ordem iguais
    for (int i = 2; i <= vertices; i++){
        if (g->A[i].min >= g->A[i].ordem){
            arestaCritica[*cont] = (char) i;
            (*cont)++;
            arestaCritica[*cont] = '-';
            (*cont)++;
            arestaCritica[*cont] = (char) g->A[i].pai;
            (*cont)++;
            arestaCritica[*cont] = ',';
            (*cont)++;
        }; 
    }

    if ((*cont) != 0) return false;
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

    if(!ehBiconexo(gr, arestaCritica, &qntdeDeArestasCriticas)) {
        printf ("NAO EH BICONEXO\n");
        printf ("As  arestas críticas são:");


        for (int i = 0; i < qntdeDeArestasCriticas; i++)
            printf("%c", arestaCritica[i]);
        
        printf("\n");
    }
    else printf("EH BICONEXO"); 

    printar(gr);
    

    return 0;
}
