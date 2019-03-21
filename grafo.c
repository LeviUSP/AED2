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

    struct vertice* pai;
    NO* cab;
}VERTICE;

typedef struct{
    int vertices;
    VERTICE A[MAX+1];//array de vertices
}GRAFO;

void resetarGrafo (GRAFO* g){
    for(int i = 1; i <= g->vertices; i++)
        g->A[i].cor = g->A[i].pai = -1;
}

void buscaBiconexo(GRAFO* g, VERTICE* v, int* contador){
    v->min = v->ordem;
    NO* p = v->cab;
    while(p){
        VERTICE* u = &(g->A[p->numeroDoVertice]);
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
    v->cor = 2;
};


bool ehBiconexo(GRAFO* g, char* arestaCritica){
    int vertices = g->vertices;
    int contador = 1;

    resetarGrafo(g);

    VERTICE v = g->A[1];
    v.cor = 0;
    v.ordem = contador; 
    buscaBiconexo(g, &v, &contador);

    if (contador < vertices){ 
        printf ("NAO EH CONEXO");
        return false;
    };

    int j = 0;
    //o primeiro elemento sempre terá o minimo e ordem iguais
    for (int i = 2; i <= vertices; i++){
        VERTICE v = g->A[i];
        if (v.min >= v.ordem){
            arestaCritica[j] = i + '-' + g->A[i].pai;
            j++;
        }; 
    }

    return true;
};


int main(){
    return 0;
}
