#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h" //inclui os Protótipos

struct NO
{
    int info;
    struct NO *esq;
    struct NO *dir;
};

ArvBin* cria_ArvBin()
{
    ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_NO(struct NO* no)
{
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvBin(ArvBin* raiz)
{
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada nó
    free(raiz);//libera a raiz
}

int insere_ArvBin(ArvBin* raiz, int valor)
{
    if(raiz == NULL)
        return 0;
    struct NO* novo;
    novo = (struct NO*) malloc(sizeof(struct NO));
    if(novo == NULL)
        return 0;
    novo->info = valor;
    novo->dir = NULL;
    novo->esq = NULL;

    if(*raiz == NULL)
        *raiz = novo;
    else
    {
        struct NO* atual = *raiz;
        struct NO* ant = NULL;
        while(atual != NULL)
        {
            ant = atual;
            if(valor == atual->info)
            {
                free(novo);
                return 0;//elemento já existe
            }

            if(valor > atual->info)
                atual = atual->dir;
            else
                atual = atual->esq;
        }
        if(valor > ant->info)
            ant->dir = novo;
        else
            ant->esq = novo;
    }
    return 1;
}

// http://www.ime.usp.br/~pf/algoritmos/aulas/binst.html
int remove_ArvBin(ArvBin *raiz, int valor)
{
    if(raiz == NULL)
        return 0;
    struct NO* ant = NULL;
    struct NO* atual = *raiz;
    while(atual != NULL)
    {
        if(valor == atual->info)
        {
            if(atual == *raiz)
                *raiz = remove_atual(atual);
            else
            {
                if(ant->dir == atual)
                    ant->dir = remove_atual(atual);
                else
                    ant->esq = remove_atual(atual);
            }
            return 1;
        }
        ant = atual;
        if(valor > atual->info)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}

int estaVazia_ArvBin(ArvBin *raiz)
{
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}

struct NO* remove_atual(struct NO* atual)
{
    struct NO *no1, *no2;
    if(atual->esq == NULL)
    {
        no2 = atual->dir;
        free(atual);
        return no2;
    }
    no1 = atual;
    no2 = atual->esq;
    while(no2->dir != NULL)
    {
        no1 = no2;
        no2 = no2->dir;
    }
    // no2 é o nó anterior a r na ordem e-r-d
    // no1 é o pai de no2
    if(no1 != atual)
    {
        no1->dir = no2->esq;
        no2->esq = atual->esq;
    }
    no2->dir = atual->dir;
    free(atual);
    return no2;
}

int altura_ArvBin(ArvBin *raiz)
{
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = altura_ArvBin(&((*raiz)->esq));
    int alt_dir = altura_ArvBin(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}


void preOrdem_ArvBin(ArvBin *raiz)
{
    if(raiz == NULL)
        return;
    if(*raiz != NULL)
    {
        printf("%d\n",(*raiz)->info);
        preOrdem_ArvBin(&((*raiz)->esq));
        preOrdem_ArvBin(&((*raiz)->dir));
    }
}

/*
1) Faça uma função que calcula quantos nós folha uma determinada árvore
possui. Nó folha é aquele nó que não possui filhos.
*/

int contador_de_nos_foia(ArvBin *raiz)
{
    if (raiz == NULL || *raiz == NULL)
        return 0;

    if ((*raiz)->esq == NULL && (*raiz)->dir == NULL)
        return 1;

    return contador_de_nos_foia(&((*raiz)->esq)) +
           contador_de_nos_foia(&((*raiz)->dir));
}

/*
2) Faça uma função para imprimir a árvore de modo que seja possível
identificar os nós filhos, pais e folhas.
*/

void imprime_ArvBin_Detalhada(ArvBin *raiz)
{
    if(raiz == NULL || *raiz == NULL)
    {
        printf("Arvore vazia!\n");
        return;
    }

    printf("\n========== ESTRUTURA DA ARVORE ==========\n\n");
    imprime_NO_Detalhado(*raiz, NULL, 0);
    printf("\n=========================================\n");
}

void imprime_NO_Detalhado(struct NO* no, struct NO* pai, int nivel)
{
    if(no == NULL)
        return;

    for(int i = 0; i < nivel; i++)
        printf("    ");

    printf("No: %d ", no->info);

    if(pai == NULL)
        printf("[RAIZ]");
    else if(no->esq == NULL && no->dir == NULL)
        printf("[FOLHA]");
    else
        printf("[INTERMEDIARIO]");

    if(pai != NULL)
        printf(" (Pai: %d)", pai->info);

    if(no->esq != NULL || no->dir != NULL)
    {
        printf(" -> Filhos: ");
        if(no->esq != NULL)
            printf("Esq(%d) ", no->esq->info);
        if(no->dir != NULL)
            printf("Dir(%d)", no->dir->info);
    }

    printf("\n");

    imprime_NO_Detalhado(no->esq, no, nivel + 1);
    imprime_NO_Detalhado(no->dir, no, nivel + 1);
}


/*
3) Faça uma função que retorna quantas vezes um determinado valor
apareceu na árvore.
*/

int conta_ocorrencias_ArvBin(ArvBin *raiz, int valor)
{
    if(raiz == NULL)
        return 0;
    if(*raiz == NULL)
        return 0;

    return conta_ocorrencias_NO(*raiz, valor);
}

int conta_ocorrencias_NO(struct NO* no, int valor)
{
    if(no == NULL)
        return 0;

    int contador = 0;

    if(no->info == valor)
        contador = 1;

    contador += conta_ocorrencias_NO(no->esq, valor);
    contador += conta_ocorrencias_NO(no->dir, valor);

    return contador;
}

/*
4) Faça uma função que imprime os nós folhas de uma árvore em ordem
decrescente.
*/

void imprime_folhas_decrescente(ArvBin *raiz)
{
    if(raiz == NULL)
    {
        printf("Arvore vazia!\n");
        return;
    }
    if(*raiz == NULL)
    {
        printf("Arvore vazia!\n");
        return;
    }

    printf("Nos folhas em ordem decrescente: ");
    imprime_folhas_decrescente_NO(*raiz);
    printf("\n");
}

void imprime_folhas_decrescente_NO(struct NO* no)
{
    if(no == NULL)
        return;

    imprime_folhas_decrescente_NO(no->dir);

    if(no->esq == NULL && no->dir == NULL)
        printf("%d ", no->info);

    imprime_folhas_decrescente_NO(no->esq);
}

/*
5) Faça uma função que verifique quando duas árvores são iguais.
*/

int arvores_iguais(ArvBin *raiz1, ArvBin *raiz2)
{

    if(raiz1 == NULL && raiz2 == NULL)
        return 1;

    if(raiz1 == NULL || raiz2 == NULL)
        return 0;

    return compara_nos(*raiz1, *raiz2);
}

int compara_nos(struct NO* no1, struct NO* no2)
{
    if(no1 == NULL && no2 == NULL)
        return 1;

    if(no1 == NULL || no2 == NULL)
        return 0;

    return (no1->info == no2->info) &&
           compara_nos(no1->esq, no2->esq) &&
           compara_nos(no1->dir, no2->dir);
}

/*
6) Faça uma função que elimine todos os valores pares da árvore.
*/

void remove_pares_ArvBin(ArvBin *raiz)
{
    if(raiz == NULL || *raiz == NULL)
        return;

    int *pares = (int*) malloc(1000 * sizeof(int));
    if(pares == NULL)
        return;

    int count = 0;

    coleta_pares(*raiz, pares, &count);

    printf("Removendo valores pares: ");
    for(int i = 0; i < count; i++)
    {
        printf("%d ", pares[i]);
        remove_ArvBin(raiz, pares[i]);
    }

    if(count == 0)
        printf("Nenhum valor par encontrado");

    printf("\n");

    free(pares);
}

void coleta_pares(struct NO* no, int* pares, int* count)
{
    if(no == NULL)
        return;

    if(no->info % 2 == 0)
    {
        pares[*count] = no->info;
        (*count)++;
    }

    coleta_pares(no->esq, pares, count);
    coleta_pares(no->dir, pares, count);
}

/*
7) Duas árvores binárias são SIMILARES se possuem a mesma
distribuição de nós (independente dos valores nos mesmos). Em uma
definição mais formal, duas árvores são similares se são ambas vazia,
ou se suas sub árvores esquerdas são similares, e suas sub árvores
direitas também são similares. Crie uma função que verifica se duas
árvores são similares.
*/

int sao_similares(ArvBin *raiz1, ArvBin *raiz2)
{

    if(raiz1 == NULL && raiz2 == NULL)
        return 1;


    if(*raiz1 == NULL && *raiz2 == NULL)
        return 1;


    if(*raiz1 == NULL || *raiz2 == NULL)
        return 0;

    return sao_similares(&((*raiz1)->esq), &((*raiz2)->esq)) &&
           sao_similares(&((*raiz1)->dir), &((*raiz2)->dir));
}

/*
8) Dada uma árvore binária vazia, insira e imprima os seguintes elementos
na ordem que é mostrada: M, F, S, D, J, P, U, A, E, H, Q, T, W, K.
*/
void preOrdem_ArvBin_Char(ArvBin *raiz)
{
    if(raiz == NULL)
        return;
    if(*raiz != NULL)
    {
        printf("%c\n", (*raiz)->info);  // %c em vez de %d
        preOrdem_ArvBin_Char(&((*raiz)->esq));
        preOrdem_ArvBin_Char(&((*raiz)->dir));
    }
}

/*
9) A árvore binária abaixo representa operações matemáticas.

A expressão corresponde da figura é (6-3) * (4-1) + 5, com nós folhas
representando números e os demais nós os operadores. O resultado do
cálculo é 20. Para criar árvores com expressões matemáticas é preciso
colocar os elementos a serem inseridos nas ordens infixa ou prefixa ou
posfixa, onde cada forma representa diferente resultado nas inserções.
Os operadores bem como os números nesses tipos de árvores
normalmente são representados por variáveis do tipo char. Assim, faça o
que se pede:

a) Crie uma nova função de inserção que trate os números e
operadores e construa a árvore da imagem acima.
b) Faça uma função que imprime o resultado das operações da
árvore, no exemplo da árvore acima o resultado seria 20.
c) Imprima a árvore usando as notações infixa, prefixa e posfixa.
*/
struct NO_ex9
{
    char info;
    struct NO_ex9 *esq;
    struct NO_ex9 *dir;
};
typedef struct NO_ex9* ArvBin_ex9;

// ===== FUNÇÕES BÁSICAS =====
ArvBin_ex9* cria_ArvBin_ex9()
{
    ArvBin_ex9* raiz = (ArvBin_ex9*) malloc(sizeof(ArvBin_ex9));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_NO_ex9(struct NO_ex9* no)
{
    if(no == NULL)
        return;
    libera_NO_ex9(no->esq);
    libera_NO_ex9(no->dir);
    free(no);
}

void libera_ArvBin_ex9(ArvBin_ex9* raiz)
{
    if(raiz == NULL)
        return;
    libera_NO_ex9(*raiz);
    free(raiz);
}

// ===== a) FUNÇÃO DE INSERÇÃO PARA EXPRESSÕES =====
// Função auxiliar para criar um nó
struct NO_ex9* cria_no_ex9(char valor)
{
    struct NO_ex9* novo = (struct NO_ex9*) malloc(sizeof(struct NO_ex9));
    if(novo != NULL)
    {
        novo->info = valor;
        novo->esq = NULL;
        novo->dir = NULL;
    }
    return novo;
}

// Verifica se é operador
int eh_operador(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Insere expressão a partir de notação POSFIXA
// Exemplo: "63-41-*5+" representa (6-3)*(4-1)+5
struct NO_ex9* insere_expressao_posfixa(char* expressao)
{
    struct NO_ex9* pilha[100];
    int topo = -1;

    for(int i = 0; expressao[i] != '\0'; i++)
    {
        char c = expressao[i];

        if(isdigit(c))
        {
            pilha[++topo] = cria_no_ex9(c);
        }
        else if(eh_operador(c))
        {
            struct NO_ex9* novo = cria_no_ex9(c);
            novo->dir = pilha[topo--];
            novo->esq = pilha[topo--];
            pilha[++topo] = novo;
        }
    }

    return pilha[topo];
}

// ===== b) FUNÇÃO PARA CALCULAR O RESULTADO =====
int calcula_expressao(struct NO_ex9* no)
{
    if(no == NULL)
        return 0;

    if(no->esq == NULL && no->dir == NULL)
        return (no->info - '0');

    int esq = calcula_expressao(no->esq);
    int dir = calcula_expressao(no->dir);

    switch(no->info)
    {
    case '+':
        return esq + dir;
    case '-':
        return esq - dir;
    case '*':
        return esq * dir;
    case '/':
        return esq / dir;
    default:
        return 0;
    }
}

// ===== c) FUNÇÕES DE IMPRESSÃO (INFIXA, PREFIXA, POSFIXA) =====
void preOrdem_ex9(struct NO_ex9* no)
{
    if(no != NULL)
    {
        printf("%c ", no->info);
        preOrdem_ex9(no->esq);
        preOrdem_ex9(no->dir);
    }
}

void emOrdem_ex9(struct NO_ex9* no)
{
    if(no != NULL)
    {
        if(eh_operador(no->info))
            printf("(");

        emOrdem_ex9(no->esq);
        printf("%c", no->info);
        emOrdem_ex9(no->dir);

        if(eh_operador(no->info))
            printf(")");
    }
}

void posOrdem_ex9(struct NO_ex9* no)
{
    if(no != NULL)
    {
        posOrdem_ex9(no->esq);
        posOrdem_ex9(no->dir);
        printf("%c ", no->info);
    }
}
