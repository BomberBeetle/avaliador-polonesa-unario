#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "lexico.h"


int ch;
TokenType token;                 /// Mant�m o token atual
char tokenString[MAX_TEXT + 1];  /// Mant�m a string relativa ao token (lexema)
int lineno = 1;
int unary;
FILE *source;
FILE *listing;

///----------------------------------------------------------------------------
TokenType getToken(void)
{
   int i = 0;
   /// Pula todos os espa�os em branco
   /// ' ' espa�o em branco, '\n' nova linha, '\t' tab horizontal,
   /// '\v' tab vertical, '\f' form feed, '\r' retorno de carro

   do {
     ch = getc(source);
     if (ch == '\n')
        lineno++;
   } while (isspace(ch));

   token = NONE; /// Inicialmente, o token est� indefinido,
                 /// mas sempre ser� definido em getToken()

   switch (ch) {
     case '+':
        token = PLUS;
        break;
     case '-':
         token = MINUS;
        break;
     case '*':
         token = TIMES;
        break;
     case '/':
         token = OVER;
        break;
     case ';':
         token = SEMI;
        break;
     case '(':
        token = LPAREN;
        break;
     case ')':
         token = RPAREN;
        break;
     case '=':
        token = ASSIGN;
        break;
     case '#':
        token = UNSUB;
        break;
     case '$':
        token = UNADD;
        break;
     case EOF:
        token = ENDFILE;
        break;
   }

   switch (token) {
     case PLUS:
     case MINUS:
     case TIMES:
     case OVER:
     case SEMI:
     case LPAREN:
     case RPAREN:
     case ASSIGN:
     case UNADD:
     case UNSUB:
         tokenString[i] = ch;
         i++;
     case ENDFILE:
       tokenString[i] = '\0';
       return token;
       break;
     default:
       break;
   }
   /// Se chegar aqui, s� restam as possibilidades:
   /// ID, NUM

   ///Primeiramente vamos tratar NUM.
   ///Um num � uma sequ�ncia de digitos. N�o aceita casas decimais!
   if (isdigit(ch)) {
       do {
         tokenString[i] = ch;
         ch = getc(source);
         i++;
       } while (isdigit(ch));
       tokenString[i] = '\0';
       //Quando cair aqui, leu um caractere que n�o deveria ter lido!
       ungetc(ch, source);
       token = NUM;
       return token;
   }

   if (isalpha(ch)) {
         do {

         tokenString[i] = ch;
         ch = getc(source);
         i++;
       } while (isalpha(ch));
       tokenString[i] = '\0';
       //Quando cair aqui, leu um caractere que n�o deveria ter lido!
       ungetc(ch, source);
       token = ID;
       return token;
   }
   /// Erro no analisador l�xico, pois leu um s�mbolo de caractere
   /// que n�o faz parte do alfabeto da linguagem
   token = ERROR;
   tokenString[0] = '\0';
   return token;
}

///----------------------------------------------------------------------------
void printToken( TokenType token, const char* tokenString )
{
    switch (token) {
            case PLUS:
                fprintf(listing, "Linha %3d  lexema %s token = PLUS\n", lineno, tokenString);
                break;
            case MINUS:
                fprintf(listing, "Linha %3d  lexema %s token = MINUS\n", lineno, tokenString);
                break;
            case TIMES:
                fprintf(listing, "Linha %3d  lexema %s token = TIMES\n", lineno, tokenString);
                break;
            case OVER:
                fprintf(listing, "Linha %3d  lexema %s token = OVER\n", lineno, tokenString);
                break;
            case SEMI:
                fprintf(listing, "Linha %3d  lexema %s token = SEMI\n", lineno, tokenString);
                break;
            case LPAREN:
                fprintf(listing, "Linha %3d  lexema %s token = LPAREN\n", lineno, tokenString);
                break;
            case RPAREN:
                fprintf(listing, "Linha %3d  lexema %s token = RPAREN\n", lineno, tokenString);
                break;
            case ASSIGN:
                fprintf(listing, "Linha %3d  lexema %s token = ASSIGN\n", lineno, tokenString);
                break;
            case ID:
                fprintf(listing, "Linha %3d  lexema %s token = ID\n", lineno, tokenString);
                break;
            case NUM:
                fprintf(listing, "Linha %3d  lexema %s token = NUM\n", lineno, tokenString);
                break;
            case ERROR:
                fprintf(listing, "Linha %3d  lexema %s token = ERROR\n", lineno, tokenString);
                break;
            default:
                fprintf(listing, "Linha %3d  lexema %s token = IMPOSSIVEL\n", lineno, tokenString);
                break;
        }
}

///----------------------------------------------------------------------------
void  rodaAnalisadorLexico(char* _source)
{
    source = fopen(_source, "r");
    while (getToken() != ENDFILE) {
        printToken(token, tokenString);
    }
}
