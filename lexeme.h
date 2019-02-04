/*
 * Matthew Rinne
 * lexeme.h
 * cs403 Programming Languages
 */

#ifndef __LEXEME_INCLUDED__
#define __LEXEME_INCLUDED__


#include <stdio.h>


typedef struct lexeme Lexeme;


Lexeme *newLexeme(char *x);
Lexeme *newLexemeInt(int x);
Lexeme *newLexemeReal(double x);
Lexeme *newLexemeString(char *x);
Lexeme *newLexemeID(char *x);
char   *getLexemeType(Lexeme *n);
int     getLexemeIval(Lexeme *n);
double  getLexemeRval(Lexeme *n);
char   *getLexemeSval(Lexeme *n);
char   *getLexemeID(Lexeme *n);
Lexeme *car(Lexeme *l); /* gets lchild */
Lexeme *cdr(Lexeme *l); /* gets rchild */
void    set_car(Lexeme *parent, Lexeme *child);
void    set_cdr(Lexeme *parent, Lexeme *child);

#endif