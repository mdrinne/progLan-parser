/*
 * Matthew Rinne
 * lexical-analyzer.h
 * cs403 Programming Languages
 */


#include "lexeme.h"


void    skipComment();
int     isWhiteSpace(char ch);
void    skipWhiteSpace();
void    pushback(char ch);
char    readChar();
double  toReal(char *buf);
int     toInt(char *buf);
Lexeme *lexNumber();
Lexeme *lexVarOrKeyword();
Lexeme *lexString();
Lexeme *lex();
void    getFile(FILE *f);
int     getLine();