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
Lexeme *newLexemeVar(char *x);
char   *getLexemeType(Lexeme *n);
int     getLexemeIval(Lexeme *n);
double  getLexemeRval(Lexeme *n);
char   *getLexemeSval(Lexeme *n);
char   *getLexemeID(Lexeme *n);

#endif