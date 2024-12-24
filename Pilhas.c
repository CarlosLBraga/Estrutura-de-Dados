#include <stdio.h>
#include <stdlib.h>

typedef struct lista {
    int info;
    struct lista* prox;
} TLista;

typedef struct pilha{
    TLista *topo;
} TPilha;


TPilha *inicializa() {
    TPilha *pilha = (TPilha *)malloc(sizeof(TPilha));
    pilha->topo = NULL;
    return pilha;
}

void libera(TPilha *p) {
    TLista *q = p->topo;
    TLista *r;
    while(q != NULL){
        r = q;
        q=q->prox;
        free(r);
    }
    free(p);
}

int pilha_vazia(TPilha *pilha) {
    if (pilha->topo == NULL)
        return 1; //pilha vazia
    else
        return 0; //pilha tem pelo menos 1 elemento
}

/* *
 * Insere elem no topo da pilha
 * */
void push(TPilha *pilha, int elem) {
    TLista *novo = (TLista*) malloc(sizeof(TLista));
    novo->info = elem;
    novo->prox = pilha->topo;
    pilha->topo = novo;
}

/* *
 * Exclui o elemento do topo da pilha
 * retorna o info do elemento excluído
 */
int pop(TPilha *pilha) {
    if (pilha_vazia(pilha)) {
        exit(1);
    }
    else {
        TLista *aux = pilha->topo;
        int info = aux->info;
        pilha->topo = aux->prox;
        free(aux);
        return info;
    }
}

/* *
 * Consulta o elemento do topo da pilha
 * retorna info do elemento do topo
 */
int peek(TPilha *pilha) {
    if (pilha_vazia(pilha))
        return NULL;
    else {
        //faz consulta
        return pilha->topo->info;
    }
}

/**
* Fazer a função imprime usando as funções pop e push
* DICA: usar uma pilha auxiliar
*/
void imprime_pilha(TPilha *pilha) {
    printf("\nEstado atual da Pilha:\n");

    
    TPilha *aux = inicializa();

    
    while (!pilha_vazia(pilha)) {
        
        int pega = pop(pilha); // pegando
    
        printf(" %d\n", pega);
        push (aux, pega);
    
        
        //FAZER CODIGO AQUI
    }
    while (!pilha_vazia(aux)) {

        int devolve = pop (aux); // devolvendo
        push (pilha, devolve);
        //FAZER CODIGO AQUI
    }
    libera(aux);
    printf("\n");
}

int main() {
    TPilha *pilha = inicializa();
    push(pilha, 5);
    printf("topo: %d\n", peek(pilha));
    push(pilha, 4);
    printf("topo: %d\n", peek(pilha));
    push(pilha, 3);
    printf("topo: %d\n", peek(pilha));
    push(pilha, 7);
    printf("topo: %d\n", peek(pilha));
    push(pilha, 11);
    printf("topo: %d\n", peek(pilha));
    
    

    imprime_pilha(pilha);

    int info = pop(pilha);
    printf("elemento removido: %d\n", info);

    imprime_pilha(pilha);
}
