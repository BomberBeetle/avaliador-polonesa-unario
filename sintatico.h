#ifndef SINTATICO_H_INCLUDED
#define SINTATICO_H_INCLUDED

void statement(void);
void status_stmt(void);
void print_stmt(void);
void match(TokenType expected);
void syntaxError(char * message);
void stmt_sequence(void);
void parse();


#endif // SINTATICO_H_INCLUDED
