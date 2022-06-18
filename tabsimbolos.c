#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tabsimbolos.h"

///Uma posi��o para cada letra de A...Z
idNode tabelaSimbolos[] =   {{'A', 1},  {'B', 2},  {'C', 3},  {'D', 4},  {'E', 5},
                             {'F', 6},  {'G', 7},  {'H', 8},  {'I', 9},  {'J', 10},
                             {'K', 11}, {'L', 12}, {'M', 13}, {'N', 14}, {'O', 15},
                             {'P', 16}, {'Q', 17}, {'R', 18}, {'S', 19}, {'T', 20},
                             {'U', 21}, {'V', 22}, {'W', 23}, {'X', 24}, {'Y', 25},
                             {'Z', 26}
                            };

///1) Todos os operandos v�o direto para a sa�da, n�o passam pela pilha.
///2) Todos os operadores v�o para a pilha porque est�o no meio como em A + B.
///3) A quest�o � saber o que fazer na presen�a de outro operador no topo da pilha.
///   Por exemplo A * B + C deve virar AB*C+
///   Quando o + � encontrado na entrada, verifique que tem o * no topo da pilha.
///   Esse * � desempilhado, gerando AB*. Isso porque o * tem maior prioridade que o +
///   Da� o + � empilhado.
///   Na sequ�ncia, O C vai para a sa�da gerando AB*C
///   Com o final da entrada, tudo da pilha � desempilhado e colocado na sa�da,
///   gerando AB*C+
///4) Ao comparar algum operador na entrada com outro na pilha, aquele com maior valor vai para a sa�da.
///   Se o da pilha tem maior valor, � desempilhado.
///   Se o da entrada tem maior valor, � empilhado.
///5) Uma abertura de par�nteses sempre vai para a pilha, pois n�o sabemos quando fecha
///   Por isso tem a maior preced�ncia de todos: 5.
///6) Fechamento de par�nteses n�o tem prioridade na pilha, porque nunca � empilhado
///   Quando um fechamento de par�nteses � encontrado, tudo � desempilhado at� chegar na
///   abertura de par�nteses que deve estar na pilha.
///7) * e / na pilha, t�m preced�ncia a * e / na entrada
///8) + e - na pilha, t�m preced�ncia a + e - na entrada
Prec tabelaPrecedencia[8] = { {')', -1, 0},
                              {'(',  0, 5},
                              {'+',  2, 1},
                              {'-',  2, 1},
                              {'*',  4, 3},
                              {'/',  4, 3},
                              {'#',  5, 4},
                              {'$', 5, 4}
                            };

///----------------------------------------------------------------------------
void imprimeTabelaSimbolos(FILE* file)
{
    fprintf(file, "-------------------- STATUS --------------------\n");
    for (int i=0; i < TOTAL_VARS; i++) {
       fprintf(file, "ID = %3c value = %10.2f\n", tabelaSimbolos[i].id, tabelaSimbolos[i].value);
    }
    fprintf(file, "------------------------------------------------\n");
}

///----------------------------------------------------------------------------
void imprimeSimbolo(FILE* file, char id)
{
   fprintf(file, "ID = %3c value = %10.2f\n", tabelaSimbolos[id - 'A'].id, tabelaSimbolos[id - 'A'].value);
}


///----------------------------------------------------------------------------
void testaTabelaSimbolos()
{
   imprimeTabelaSimbolos(stdout);
   imprimeSimbolo(stdout, 'C');

}

///----------------------------------------------------------------------------
int prioridadeEntrada(char c)
{
    for (int i = 0; i < 8; i++)
        if (c == tabelaPrecedencia[i].op)
            return tabelaPrecedencia[i].inInput;
    return -1; //N�o � para acontecer!

}

///----------------------------------------------------------------------------
int prioridadePilha(char c)
{
    for (int i = 0; i < 8; i++)
        if (c == tabelaPrecedencia[i].op)
            return tabelaPrecedencia[i].onStack;
    return -1; //N�o � para acontecer!
}
