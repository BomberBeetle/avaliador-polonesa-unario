#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "pilhaExp.h"
#include "tabsimbolos.h"

///----------------------------------------------------------------------------
PilhaExp* criaPilhaExp()
{
    PilhaExp* ret = malloc(sizeof(PilhaExp));
     if (ret == NULL) {   //Falhou alocação da estrutura
        fprintf(stderr, "Memória esgotada na função %s - (%d)\n", __FUNCTION__, __LINE__);
        exit(0);
    }
    ret->primeiro = NULL;
    return ret;
}

///----------------------------------------------------------------------------
void destroiPilhaExp(PilhaExp* pilha)
{
    if (pilha != NULL) {
        ExpEl* curr = pilha->primeiro;
        while (curr != NULL) {
           ExpEl* prox = curr->next;
           destroiNo(curr);
           curr = prox;
        }
        free(pilha);
    }
}

///----------------------------------------------------------------------------
void pushPilhaExp(PilhaExp* pilha, ExpEl* el)
{
    el->next = pilha->primeiro;
    pilha->primeiro = el;
}

///----------------------------------------------------------------------------
ExpEl* topPilhaExp(PilhaExp* pilha)
{
    if (pilha == NULL)
        return NULL;
    else
        return pilha->primeiro;
}

///----------------------------------------------------------------------------
ExpEl* popPilhaExp(PilhaExp* pilha)
{
    ExpEl* ret = pilha->primeiro;
    pilha->primeiro = pilha->primeiro->next;
    return ret;
}


///----------------------------------------------------------------------------
bool isEmptyPilhaExp(PilhaExp* pilha)
{
    if (pilha->primeiro == NULL)
        return true;
    else
        return false;
}

///----------------------------------------------------------------------------
void printPilhaExp(FilaExp* pilha, FILE* arq)
{
    ExpEl* curr = pilha->primeiro;
    printf("-----------------------\n");
    while (curr != NULL) {
        printf("ID    = %s\n", curr->id);
        if (isalpha(curr->id[0]) ||  isdigit(curr->id[0]))
            printf("Value = %.2f\n", curr->value);
        else
            printf("Value = -.--\n");
        curr = curr->next;
    }
    printf("-----------------------\n");
}
