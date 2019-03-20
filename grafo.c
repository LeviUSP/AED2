#include <stdio.h>
#include <stdbool.h>

#define MAX 100

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
    VERTICE A[MAX+1];//array de vertices
}GRAFO;

void inicializarGrafo(GRAFO* g){

}

void resetarGrafo (GRAFO* g){
    for(int i = 1; i <= g->vertices; i++){
        VERTICE v = g->A[i];
        v.cor = -1;
        v.pai = -1;
    };
}

void buscaBiconexo(GRAFO* g, VERTICE* v, int* contador){
    v->min = v->ordem;
    NO* p = v.cab;
    while(p){
        VERTICE* u = g->A[p->numeroDoVertice];
        if(u->cor == -1){
            u->cor = 0;
            u->pai = v;
            u->ordem = ++(*contador);
            
            buscaBiconexo(g, u, contador);
        };

        if (v->min > u->min && u != v->pai) 
            v->min = u->min;
        p = p->prox;
    }
    v->cor = 2;//preto
};

char* acharArestaCritica(GRAFO* g, int v){
    NO* p = v.cab;
};


bool ehBiconexo(GRAFO* g, char* arestaCritica){
    int vertices = g->vertices;
    int contador = 1;

    resetarGrafo(g, cor, pai);

    VERTICE v = g->A[1];
    v.cor = 0;
    v.caminho = contador; 
    buscaBiconexo(g, &v, &contador);
    v.cor = 2

    if (contador < vertices){ 
        printf ("NAO EH CONEXO");
        return false;
    };

    //o primeiro elemento sempre terá o minimo e ordem iguais
    for (int i = 2; i <= vertices; i++){
        VERTICE v = g->A[i];
        if (v.min >= v.ordem){
            arestaCritica = acharArestaCritica(g, v);
            return false;
        }; 
    }

    return true;
};







int main(){
    return 0;
}
