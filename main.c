#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "lexico.h"
#include "sintatico.h"
#include "tabsimbolos.h"


int main(int argc, char** argv)
{
  setlocale(LC_ALL, "");
  if (argc != 2){
      fprintf(stderr,"Uso: %s <Arquivo Fonte>\n",argv[0]);
      exit(1);
  }
  listing = stdout;
  //testaTabelaSimbolos();
  //rodaAnalisadorLexico(argv[1]);
  parse(argv[1]);
  return 0;
}
