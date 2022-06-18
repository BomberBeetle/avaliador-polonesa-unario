#ifndef FILAEXP_H_INCLUDED
#define FILAEXP_H_INCLUDED
#include <stdbool.h>
#include <stdio.h>

struct _ExpEl {
    char* id;             //Representa��o de constantes num�rias,  A...Z, +, -, *, /.
    float value;          //Value s� � usado pelas letras e constantes num�ricas
    struct _ExpEl* next;  //Pr�ximo n�
};
typedef struct _ExpEl ExpEl;

struct _FilaExp {
   ExpEl* primeiro;
   ExpEl* ultimo;
};
typedef struct _FilaExp FilaExp;

FilaExp* criaFilaExp();
ExpEl* alocaNo(char* lexema);
ExpEl* cloneNo(ExpEl* no);
void destroiNo(ExpEl* el);
void destroiFilaExp(FilaExp* fila);
void insereFilaExp(FilaExp* fila, ExpEl* el);
ExpEl* frenteFilaExp(FilaExp* fila);
ExpEl* removeFilaExp(FilaExp* fila);
bool isEmptyFilaExp(FilaExp* fila);
void printFilaExp(FilaExp* fila, FILE* arq);

#endif // FILAEXP_H_INCLUDED
