#include <stdio.h>
#include <stdbool.h>

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

    struct vertice* pai;
    NO* cab;
}VERTICE;

typedef struct{
    int vertices;
    VERTICE A[MAX+1];//array de vertices
}GRAFO;

GRAFO* criarGrafo(int numerodeVertices){
    GRAFO* gr = (GRAFO*) malloc (sizeof(GRAFO));
    gr->vertices = numerodeVertices;

    for(int i = 1; i <= numerodeVertices; i++)
        gr->A[i].numero = i;

    return gr;
}

void adicionarAresta(GRAFO* g, int v, int u){

}


void buscaBiconexo(GRAFO* g, VERTICE* v, int* contador){
    v->min = v->ordem;
    NO* p = v->cab;
    while(p){
        VERTICE* u = &(g->A[p->numeroDoVertice]);
        if(u->cor == -1){
            u->cor = 'c';
            u->pai = v;
            u->ordem = ++(*contador);
            
            buscaBiconexo(g, u, contador);
        };

        if (v->min > u->min && u != v->pai) 
            v->min = u->min;
        p = p->prox;
    }
    v->cor = 'p';
};



bool ehBiconexo(GRAFO* g, char* arestaCritica){
    int vertices = g->vertices;
    int contador = 1;


    //resetar grafo
    for(int i = 1; i <= g->vertices; i++){
        VERTICE* atual = &(g->A[i]);
        
        atual->cor = 'b';
        atual->pai = NULL;
        atual->min = 0;
        atual->ordem = 0;
    }


    VERTICE* v = &(g->A[1]);
    v->cor = 'c';
    v->ordem = contador; 
    buscaBiconexo(g, v, &contador);
    v->cor = 'p';

    if (contador < vertices){ 
        printf ("NAO EH CONEXO");
        return false;
    };

    int j = 0;
    //o primeiro elemento sempre terá o minimo e ordem iguais
    for (int i = 2; i <= vertices; i++){
        VERTICE v = g->A[i];
        if (v.min >= v.ordem){
            arestaCritica[j] = i + '-' + v.pai->numero;
            j++;
        }; 
    }

    return true;
};


int main(){
    return 0;
}
