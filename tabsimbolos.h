#ifndef TABSIMBOLOS_H_INCLUDED
#define TABSIMBOLOS_H_INCLUDED
#include <stdio.h>

#define TOTAL_VARS 26     //Ser�o mantidas 26 vari�veis de A...Z

struct _idNode {
    char id;              //S� pode manter um �nico caractere
    float value;
};

typedef struct _idNode idNode;


///Preced�ncia na pilha e na entrada (arquivo)
struct _Prec {
    char op;
    int onStack;
    int inInput;
};
typedef struct _Prec Prec;

extern idNode tabelaSimbolos[];
float getValue(char variavel);
void testaTabelaSimbolos();

int prioridadeEntrada(char c);
int prioridadePilha(char c);
#endif // TABSIMBOLOS_H_INCLUDED
