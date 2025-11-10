#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h"
int main()
{
    int N = 8, dados[8] = {50,100,30,20,40,45,35,37};

    ArvBin* raiz = cria_ArvBin();

    int i;
    for(i=0; i < N; i++)
        insere_ArvBin(raiz,dados[i]);

    preOrdem_ArvBin(raiz);
    //emOrdem_ArvBin(raiz);
    //posOrdem_ArvBin(raiz);

    /*
    if(remove_ArvBin(raiz,50)){
        printf("removido\n");
        preOrdem_ArvBin(raiz);
    }else
        printf("NAO removido\n");
    */

//    printf("altura: %d\n",altura_ArvBin(raiz));
//    printf("total NOs: %d\n",totalNO_ArvBin(raiz));
//
//    if (consulta_ArvBin(raiz, 4, &al))
//        printf("\n%d %s\n",al.mat,al.nome);

    printf("\n");
    //contador_de_nos_foia(raiz);

    printf("%d", contador_de_nos_foia(raiz));

    printf("\n");

    imprime_ArvBin_Detalhada(raiz);

    printf("\n===== CONTAGEM DE OCORRENCIAS =====\n");

    // Testa com valores que existem
    printf("Valor 50 aparece: %d vez(es)\n", conta_ocorrencias_ArvBin(raiz, 50));
    printf("\n");

    imprime_folhas_decrescente(raiz);
    printf("\n");

    if(arvores_iguais(raiz, raiz))
        printf("raiz e raiz sao IGUAIS\n");
    else
        printf("raiz e raiz sao DIFERENTES\n");

    printf("\n");

    remove_pares_ArvBin(raiz);
    preOrdem_ArvBin(raiz);
    printf("\n");

    if(sao_similares(raiz, raiz))
        printf("\nraiz e raiz SAO SIMILARES\n");
    else
        printf("\nraiz e raiz NAO sao similares (estruturas diferentes)\n");

    ArvBin *raiz_ex8 = cria_ArvBin();

    char letras[] = {'M','F','S','D','J','P','U','A','E','H','Q','T','W','K'};
    int N_ex8 = 14;

    printf("===== INSERINDO ELEMENTOS =====\n");
    for(int i = 0; i < N_ex8; i++)
    {
        insere_ArvBin(raiz_ex8, letras[i]);
        printf("Inserido: %c\n", letras[i]);
    }

    printf("\n===== PRE-ORDEM =====\n");
    preOrdem_ArvBin_Char(raiz_ex8);

    ArvBin_ex9 *raiz_ex9 = cria_ArvBin_ex9();
    *raiz_ex9 = insere_expressao_posfixa("63-41-*5+");

    printf("===== NOTACOES =====\n");
    printf("PREFIXA:  ");
    preOrdem_ex9(*raiz_ex9);
    printf("\n");

    printf("INFIXA:   ");
    emOrdem_ex9(*raiz_ex9);
    printf("\n");

    printf("POSFIXA:  ");
    posOrdem_ex9(*raiz_ex9);
    printf("\n");

    printf("\n===== RESULTADO DO CALCULO =====\n");
    int resultado = calcula_expressao(*raiz_ex9);
    printf("Resultado: %d\n", resultado);



    printf("\nFim!\n");
    libera_ArvBin(raiz);
    libera_ArvBin(raiz_ex8);
    libera_ArvBin_ex9(raiz_ex9);
    return 0;
}
