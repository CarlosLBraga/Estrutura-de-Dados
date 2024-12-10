#include <stdio.h>
#include <stdlib.h>

//programa cria uma arvore balanceada a partir de um vetor ordenado
//ordenação feita com quick sort

// estrutura para árvore
typedef struct sNoA {

    char info;
    int chave;
    struct sNoA *esq;
    struct sNoA *dir;

} TNoA;

TNoA* insere (TNoA* no, int chave) {
    // cria uma nova estrutura tipo TNoA para inserção
    if (no == NULL) {
        no = (TNoA*) malloc(sizeof(TNoA));
        
        no->chave = chave;
        no->esq = NULL;
        no->dir = NULL;   
    }

    else if (chave < (no->chave)) {
        // verifica se a chave é menor que a chave do nó atual e insere na esquerda
        no ->esq = insere(no->esq, chave); 
    }
    else if (chave > (no->chave)) {
        no ->dir = insere(no->dir, chave);
    } 
    else {
        printf("Insere Inválida! \n"); // chave já existente
        exit(1);
    }

    return no;
}

TNoA* cria_arvore_balanceada (TNoA* raiz, int *vetor, int inicio, int fim){
    if (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        raiz = insere(raiz, vetor[meio]);
    
    // cria sub-árvores
        raiz = cria_arvore_balanceada(raiz, vetor, inicio, meio-1); // esquerda
        
        raiz = cria_arvore_balanceada(raiz, vetor, meio + 1, fim); // direita
        
    }
    return raiz;
}


//troca a posição dos elementos
void troca (int* a, int* b){
    int aux = *a;
    *a = *b;
    *b = aux;
}


// função para particionar o vetor
int particiona (int* vetor, int inicio, int fim){
    int pivo = vetor[fim];
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++){
        if (vetor[j] < pivo){
            i ++;
            troca(&vetor[i], &vetor[j]);
        }
    }
    troca (&vetor[i+1], &vetor[fim]);
    return i+1;
}

void quicksort (int* vetor, int inicio, int fim) {
    
    if (inicio < fim){
        int p = particiona(vetor, inicio, fim); // particiona o vetor
    
    
    quicksort(vetor, inicio, p - 1); // ordena a parte esquerda
    quicksort(vetor, p +1, fim); // ordena a parte direita
    }
}


void imprime_vetor (int* vetor, int tam){
    for (int i = 0; i < tam; i ++){
        printf(" %d ", vetor[i]);
    }
    
}

// impressão da árvore
void imprime_arvore (TNoA* no, int tab){
    printf("\n");
    for (int i = 0; i < tab; i++){
        printf("-");
    }
    if (no != NULL) {
        printf("%d\n", no->chave);
        imprime_arvore(no->esq, tab + 2);
        printf("\n");
        imprime_arvore(no->dir, tab + 2);
    }
    else {
        printf("vazio");
    }
}

// função para buscar um elemento na árvore recursivamente
// elementos a esquerda são menores, elementos a direita são maiores

TNoA* busca_recursiva (TNoA* no, int chave) {
    
    if (no == NULL) {
        return NULL;
    }

    else if (no->chave == chave) {
        return no;
    }

    else if (no->chave > chave) { // se a busca for menor que o nó chave, busca na esquerda
        return busca_recursiva(no->esq, chave);
    }

    else {
        return busca_recursiva (no->dir, chave); // senão busca na direita
    }
}


int main () {
    int n;
    printf("digite o tamanho do vetor: ");
    scanf("%d", &n);
    // vetor aloca dinamicamente
    int* vetor = (int* ) malloc (n * sizeof(int));

    for (int i = 0; i < n; i++) {
        printf("digite o valor da posicao %d: \n", i);
        scanf("%d", &vetor[i]);
    }
    quicksort(vetor, 0, n-1);
    printf("\n");
    printf(" VETOR \n");

    imprime_vetor(vetor, n);

    printf("\n");

    TNoA* raiz = NULL; // cria uma árvore vazia
    raiz = cria_arvore_balanceada(raiz, vetor, 0, n-1); // cria árvore balanceada com a chamada da função
    imprime_arvore(raiz, 0); // imprime a árvore

    // busca um elemento na árvore
    int chave_busca;
    printf("\n");
    printf("digite a chave para busca: ");
    scanf("%d", &chave_busca);

    TNoA* busca = busca_recursiva(raiz, chave_busca);
    // se o elemento estiver na árvore, imprime a chave
    if (busca != NULL){
        printf("elemento %d encontrado", busca->chave);
    } else {
        printf("elemento não encontrado");
    }
    
    return 0;
}
