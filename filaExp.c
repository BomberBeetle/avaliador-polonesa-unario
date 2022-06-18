#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "filaExp.h"
#include "tabsimbolos.h"

///----------------------------------------------------------------------------
FilaExp* criaFilaExp()
{
    FilaExp* ret = malloc(sizeof(FilaExp));
     if (ret == NULL) {   //Falhou alocação da estrutura
        fprintf(stderr, "Memória esgotada na função %s - (%d)\n", __FUNCTION__, __LINE__);
        exit(0);
    }
    ret->primeiro = NULL;
    ret->ultimo = NULL;
    return ret;
}

///----------------------------------------------------------------------------
ExpEl* alocaNo(char* lexema)
{
    ExpEl* ret = malloc(sizeof(ExpEl));
    if (ret == NULL) {   //Falhou alocação da estrutura
        fprintf(stderr, "Memória esgotada na função %s - (%d)\n", __FUNCTION__, __LINE__);
        exit(0);
    }
    ret->id = strdup(lexema);
    if (ret->id == NULL) {   //Falhou alocação da string
        fprintf(stderr, "Memória esgotada na função %s - (%d)\n", __FUNCTION__, __LINE__);
        exit(0);
    }

    if (isalpha(lexema[0])) {
        ret->value = tabelaSimbolos[toupper(lexema[0]) - 'A'].value;
    }
    else{
        if (isdigit(lexema[0])) {
            ret->value = atoi(lexema);
        }
        else {
            ret->value = 0.0;
        }
    }
    ret->next = NULL;
    return ret;
}

///----------------------------------------------------------------------------
ExpEl* cloneNo(ExpEl* no)
{
    ExpEl* ret = malloc(sizeof(ExpEl));
    if (ret == NULL) {   //Falhou alocação da estrutura
        fprintf(stderr, "Memória esgotada na função %s - (%d)\n", __FUNCTION__, __LINE__);
        exit(0);
    }
    ret->id = strdup(no->id);
    if (ret->id == NULL) {   //Falhou alocação da string
        fprintf(stderr, "Memória esgotada na função %s - (%d)\n", __FUNCTION__, __LINE__);
        exit(0);
    }
    ret->value = no->value;
    ret->next = no->next;
    return ret;
}

///----------------------------------------------------------------------------
void destroiNo(ExpEl* el)
{
    if (el != NULL) {
        free(el->id);
        free(el);
    }
}

///----------------------------------------------------------------------------
void destroiFilaExp(FilaExp* fila)
{
    if (fila != NULL) {
        ExpEl* curr = fila->primeiro;
        while (curr != NULL) {
           ExpEl* prox = curr->next;
           destroiNo(curr);
           curr = prox;
        }
        free(fila);
    }
}

///----------------------------------------------------------------------------
void insereFilaExp(FilaExp* fila, ExpEl* el)
{
    if (fila->primeiro == NULL) {
        fila->primeiro = el;
        fila->ultimo   = el;
    }
    else {
        fila->ultimo->next = el;
        fila->ultimo = el;
    }


}

///----------------------------------------------------------------------------
ExpEl* frenteFilaExp(FilaExp* fila)
{
    if (fila == NULL)
        return NULL;
    else
        return fila->primeiro;
}

///----------------------------------------------------------------------------
ExpEl* removeFilaExp(FilaExp* fila)
{
    ExpEl* ret = fila->primeiro;
    fila->primeiro = fila->primeiro->next;
    return ret;
}


///----------------------------------------------------------------------------
bool isEmptyFilaExp(FilaExp* fila)
{
    if (fila->primeiro == NULL)
        return true;
    else
        return false;
}

///----------------------------------------------------------------------------
void printFilaExp(FilaExp* fila, FILE* arq)
{
    ExpEl* curr = fila->primeiro;
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
