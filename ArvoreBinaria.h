
typedef struct NO* ArvBin;

ArvBin* cria_ArvBin();
void libera_ArvBin(ArvBin *raiz);
int insere_ArvBin(ArvBin* raiz, int valor);
int remove_ArvBin(ArvBin *raiz, int valor);
struct NO* remove_atual(struct NO* atual);
int estaVazia_ArvBin(ArvBin *raiz);
int altura_ArvBin(ArvBin *raiz);
int totalNO_ArvBin(ArvBin *raiz);
int consulta_ArvBin(ArvBin *raiz, int valor);
void preOrdem_ArvBin(ArvBin *raiz);
void emOrdem_ArvBin(ArvBin *raiz);
void posOrdem_ArvBin(ArvBin *raiz);

//ex1
int contador_de_nos_foia(ArvBin *raiz);

//ex2
void imprime_ArvBin_Detalhada(ArvBin *raiz);
void imprime_NO_Detalhado(struct NO* no, struct NO* pai, int nivel);

//ex3
int conta_ocorrencias_ArvBin(ArvBin *raiz, int valor);
int conta_ocorrencias_NO(struct NO* no, int valor);

//ex4
void imprime_folhas_decrescente(ArvBin *raiz);
void imprime_folhas_decrescente_NO(struct NO* no);

//ex5
int arvores_iguais(ArvBin *raiz1, ArvBin *raiz2);
int compara_nos(struct NO* no1, struct NO* no2);

//ex6
void remove_pares_ArvBin(ArvBin *raiz);
void coleta_pares(struct NO* no, int* pares, int* count);

//ex7
int sao_similares(ArvBin *raiz1, ArvBin *raiz2);

//ex8
void preOrdem_ArvBin_Char(ArvBin *raiz);

//ex9
typedef struct NO_ex9* ArvBin_ex9;
ArvBin_ex9* cria_ArvBin_ex9();
void libera_NO_ex9(struct NO_ex9* no);
void libera_ArvBin_ex9(ArvBin_ex9* raiz);

//a
struct NO_ex9* cria_no_ex9(char valor);
int eh_operador(char c);
struct NO_ex9* insere_expressao_posfixa(char* expressao);

//b
int calcula_expressao(struct NO_ex9* no);

//c
void preOrdem_ex9(struct NO_ex9* no);
void emOrdem_ex9(struct NO_ex9* no);
void posOrdem_ex9(struct NO_ex9* no);
