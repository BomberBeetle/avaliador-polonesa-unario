#ifndef PILHAEXP_H_INCLUDED
#define PILHAEXP_H_INCLUDED

#include "filaExp.h"

struct _PilhaExp {
   ExpEl* primeiro;
};
typedef struct _PilhaExp PilhaExp;

PilhaExp* criaPilhaExp();
void destroiPilhaExp(PilhaExp* pilha);
void pushPilhaExp(PilhaExp* pilha, ExpEl* el);
ExpEl* topPilhaExp(PilhaExp* pilha);
ExpEl* popPilhaExp(PilhaExp* pilha);
bool isEmptyPilhaExp(PilhaExp* pilha);
void printPilhaExp(FilaExp* pilha, FILE* arq);

#endif // PILHAEXP_H_INCLUDED
