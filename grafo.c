#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

#define MAX 100

typedef struct adj{
    int numeroDoVertice;
    int pesoDaAresta;
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
    VERTICE A[MAX+1];//array de vertices
}GRAFO;

GRAFO* criarGrafo(int numerodeVertices){
    GRAFO* gr = (GRAFO*) malloc(sizeof(GRAFO));
    gr->vertices = numerodeVertices;

    for(int i = 1; i <= numerodeVertices; i++)
        gr->A[i].numero = i;

    return gr;
}

void adicionarAresta(GRAFO* g, int v, int u){

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

        if (vertice[v].min > vertice[u].min && u != v->pai) 
            vertice[v].min = vertice[u].min;

        p = p->prox;
    }
    vertice[v].cor = 'p';
};



bool ehBiconexo(GRAFO* g, char* arestaCritica){
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
    
    v.cor = 'p';

    if (contador < vertices){ 
        printf ("NAO EH CONEXO");
        return false;
    };

    int j = 0;
    //o primeiro elemento sempre terá o minimo e ordem iguais
    for (int i = 2; i <= vertices; i++){
        if (vertice[v].min >= vertice[v].ordem){
            arestaCritica[j] = i + '-' + v.pai;
            j++;
        }; 
    }

    return true;
};


int main(){
    return 0;
}
