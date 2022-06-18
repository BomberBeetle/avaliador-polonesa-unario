#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "lexico.h"
#include "sintatico.h"
#include "tabsimbolos.h"
#include "filaExp.h"
#include "pilhaExp.h"



///----------------------------------------------------------------------------
void statement(void)
{
    FilaExp* fila = criaFilaExp();
    do {
         switch(token) {
         case ID:
         case NUM:
         case PLUS:
         case MINUS:
         case TIMES:
         case OVER:
         case LPAREN:
         case RPAREN:
         case UNADD:
         case UNSUB:
             {
                 ExpEl* el = alocaNo(tokenString);
                 insereFilaExp(fila, el);
                 match(token);
                 break;
             }

         case SEMI:
            break;
         default:
            printToken(token,tokenString);
            syntaxError("unexpected token -> ");
            break;
         }
    } while( token != SEMI);
    match(SEMI);
    printf("----------------FIM DE LEITURA DE UMA EXPRESS�O-----------------\n");
    printf("----------------EXPRESS�O NA FORMA INFIXA-----------------------\n");
    printFilaExp(fila, stdout);

    ///Agora vamos gerar a express�o na forma posfixa (polonesa reversa)
    PilhaExp* pilha = criaPilhaExp();
    FilaExp* filaPosFixa = criaFilaExp();
    ExpEl* el = fila->primeiro;
    while(el != NULL) {
        char ch = el->id[0];
        if (isdigit(ch) || isalpha(ch))
            insereFilaExp(filaPosFixa, cloneNo(el));

        if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == '#' || ch == '$') {
            while (!isEmptyPilhaExp(pilha) && prioridadePilha(topPilhaExp(pilha)->id[0]) > prioridadeEntrada(ch)) {
                ExpEl* elPilha = popPilhaExp(pilha);
                insereFilaExp(filaPosFixa, elPilha);
            }
            pushPilhaExp(pilha, cloneNo(el));
        }
        if (ch == ')') {
            ExpEl* elPilha = NULL;
            do {
                elPilha = popPilhaExp(pilha);
                if (elPilha->id[0] != '(')
                    insereFilaExp(filaPosFixa, elPilha);
            } while (elPilha->id[0] != '(');
            destroiNo(elPilha); ///Destr�i a abertura de par�nteses que n�o vai na p�s fixa
        }
        el = el->next;
    }
    ///No final, tudo que houver na pilha deve ser desempilhado e colocado na sa�da
    while (!isEmptyPilhaExp(pilha)) {
        ExpEl* elPilha = popPilhaExp(pilha);
        insereFilaExp(filaPosFixa, elPilha);
    }
    ///A fila com a express�o na nota��o polonesa reversa
    printf("----------------EXPRESS�O NA FORMA POSFIXA-----------------------\n");
    printFilaExp(filaPosFixa, stdout);

    ///Agora vamos utilizar uma pilha para calcular o valor da express�o:
    PilhaExp* pilhaCalculo = criaPilhaExp();
    while (!isEmptyFilaExp(filaPosFixa)) {
        ExpEl* elPilha = removeFilaExp(filaPosFixa);
        char ch = elPilha->id[0];
        if (isdigit(ch) || isalpha(ch)) {
            pushPilhaExp(pilhaCalculo, elPilha);
        }
        else if(ch != '#' && ch != '$'){
            ///Nesta implementa��o s� restam operadores bin�rios!
            ExpEl* operando1 = popPilhaExp(pilhaCalculo);
            ExpEl* operando2 = popPilhaExp(pilhaCalculo);
            ExpEl* operador  = cloneNo(elPilha);
            free(operador->id); //Libera o texto anterior
            int tamanho = strlen(operando1->id) + strlen(operando2->id) + strlen(elPilha->id) + 2 +1;
            operador->id = malloc(sizeof(char)* tamanho);
            sprintf(operador->id, "%s %s %s", operando2->id, operando1->id, elPilha->id);

            switch (ch) {
            case '+':
                operador->value = operando2->value + operando1->value;
                break;
            case '-':
                operador->value = operando2->value - operando1->value;
                break;
            case '*':
                operador->value = operando2->value * operando1->value;
                break;
            case '/':
                operador->value = operando2->value / operando1->value;
                break;
            default:
                //N�o deve ocorrer!
                break;

            }
            pushPilhaExp(pilhaCalculo, operador);
            destroiNo(operando1);
            destroiNo(operando2);
            destroiNo(elPilha);
        }
        else{
            ExpEl* operando1 = popPilhaExp(pilhaCalculo);
            ExpEl* operador  = cloneNo(elPilha);
            free(operador->id);
            int tamanho = strlen(operando1->id) + strlen(elPilha->id) + 2;
            operador->id = malloc(sizeof(char)* tamanho);
            sprintf(operador->id, "%s %s", operando1->id, elPilha->id);
            switch(ch){
                case '#':
                    operador->value = operando1->value--;
                    break;
                case '$':
                    operador->value = operando1->value++;
                    break;
            }
            pushPilhaExp(pilhaCalculo, operador);
            destroiNo(operando1);
            destroiNo(elPilha);
        }
    }
    ///No final, teremos empilhado o resultado da express�o
    ExpEl* resultado = popPilhaExp(pilhaCalculo);
    printf("----------------RESULTADO-----------------------\n");
    printf("A express�o na nota��o polonesa invertida: %s\n", resultado->id);
    printf("O c�lculo da express�o = %f\n", resultado->value);
    destroiNo(resultado);

    destroiPilhaExp(pilhaCalculo);
    destroiFilaExp(filaPosFixa);
    destroiPilhaExp(pilha);
    destroiFilaExp(fila);
}



///----------------------------------------------------------------------------
void stmt_sequence(void)
{
    while (token != ENDFILE){
       statement();
    }
}

///----------------------------------------------------------------------------
void syntaxError(char * message){
  fprintf(listing,"\n>>> ");
  fprintf(listing,"Syntax error at line %d: %s",lineno,message);
  exit(0);
}

///----------------------------------------------------------------------------
void match(TokenType expected){
  if (token == expected)
      token = getToken();
  else {
    printToken(token,tokenString);
    syntaxError("unexpected token ->");
  }
}

///----------------------------------------------------------------------------
void parse(char* _source)
{
    source = fopen(_source, "r");
    token = getToken();
    stmt_sequence();
    fclose(source);
}

