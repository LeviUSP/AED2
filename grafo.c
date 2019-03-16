#include <stdio.h>
#include <stdbool.h>

#define MAX 100

//I started to cry
typedef struct adj{
    int numeroDoVertice;
    int pesoDaAresta;
    struct adj* prox;
}NO;

typedef struct vertice{
    int cor;
    int ordem;
    int min;

    struct vertice pai;
    NO* cab;
}VERTICE;

typedef struct{
    int vertices;
    VERTICE A[MAX];//array de vertices
}GRAFO;

void resetarGrafo (GRAFO* g){
    for(int i = 0; i < g->vertices; i++){
        VERTICE v = g->A[i];
        v.cor = -1;
        v.pai = -1;
    };
}

void buscaBiconexo(GRAFO* g, VERTICE v, int* contador){
    v.min = v.ordem;
    NO* p = v.cab;
    while(p){
        VERTICE u = g->A[p->numeroDoVertice];
        if(u.cor == -1){
            u.cor = 0;
            u.pai = v;
            u.ordem = ++(*contador);
            
            buscaBiconexo(g, u, contador);
        };

        if (v.min > u.min && u != v.pai) 
            v.min = u.min;
        p = p->prox;
    }
    v.cor = 2;
};

bool ehBiconexo(GRAFO* g, char* arestaCritica){
    int vertices = g->vertices;
    
    
    int cor[vertices];// 0-cinza e 1-preto
    int pai[vertices];
    int caminho[vertices];
    int min[vertices];
    int contador = 1;


    resetarGrafo(g, cor, pai);

    int v = 0;
    cor[v] = 0;
    caminho[v] = contador; 
    buscaBiconexo(g, v, cor, pai, caminho, min, contador);

    int j = 0;
    for (int i = 0; i < vertices; i++){
        if(cor[i]==1 || (caminho[i] != 1 && min[i] >= caminho[i])){ 
            arestaCritica = acharArestaCritica(g, i);
            return false;
        }
        j++;
    }

    return true;
};

char* acharArestaCritica(GRAFO* g, int v){

};






int main(){
    return 0;
}
