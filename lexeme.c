/*
 * Matthew Rinne
 * lexeme.c
 * cs403 Programming Languages
 */


#include "lexeme.h"
#include "types.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>


struct lexeme
{
    char   *type;
    int     ival;
    double  rval;
    char   *sval;
    char   *ID;
} ;


Lexeme *
newLexeme(char *x)
{
    Lexeme *new = malloc(sizeof(Lexeme));
    assert(new != 0);
    new->type = x;
    return new;
}


Lexeme *
newLexemeInt(int x)
{
    Lexeme *new = malloc(sizeof(Lexeme));
    assert(new != 0);
    new->type = INTEGER;
    new->ival = x;
    return new;
}


Lexeme *
newLexemeReal(double x)
{
    Lexeme *new = malloc(sizeof(Lexeme));
    assert(new != 0);
    new->type = REAL;
    new->rval = x;
    return new;
}


Lexeme *
newLexemeString(char *x)
{
    Lexeme *new = malloc(sizeof(Lexeme));
    assert(new != 0);
    new->type = STRING;
    new->sval = x;
    return new;
}


Lexeme *
newLexemeVar(char *x)
{
    Lexeme *new = malloc(sizeof(Lexeme));
    assert(new != 0);
    new->type = VARIABLE;
    new->ID   = x;
    return new;
}


char *
getLexemeType(Lexeme *n)
{
    return n->type;
}


int
getLexemeIval(Lexeme *n)
{
    return n->ival;
}


double
getLexemeRval(Lexeme *n)
{
    return n->rval;
}


char *
getLexemeSval(Lexeme *n)
{
    return n->sval;
}


char *
getLexemeID(Lexeme *n)
{
    return n->ID;
}
