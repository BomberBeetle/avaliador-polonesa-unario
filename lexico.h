#include <stdio.h>

#ifndef LEXICO_H_INCLUDED
#define LEXICO_H_INCLUDED

///Tamanho m�ximo de uma vari�vel
#define MAX_TEXT 1024

typedef enum {
              ///Tokens de controle
              ENDFILE, ERROR, NONE,
              ///Tokens de lexemas multicaracteres
              ID, NUM,
              ///S�mbolos especiais
              ASSIGN, PLUS, MINUS, TIMES, OVER, LPAREN, RPAREN, SEMI, UNADD, UNSUB
} TokenType;


extern FILE* source;   /// Arquivo de c�digo fonte
extern FILE* listing;  /// Arquivo de listagem de sa�da
extern FILE* code;     /// C�digos de execu��o gerados

extern int lineno;     /// N�mero de linha no c�digo fonte para listagem

extern TokenType token;                 /// Mant�m o token atual
extern char tokenString[MAX_TEXT + 1];  /// Mant�m a string relativa ao token (lexema)

void  rodaAnalisadorLexico(char* _source);
TokenType getToken(void);
void printToken( TokenType token, const char* tokenString );

#endif // LEXICO_H_INCLUDED
