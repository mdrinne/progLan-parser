/*
 * Matthew Rinne
 * parser.c
 * cs403 Programming Languages
 */

#include "lexer.h"
#include "lexeme.h"
#include "types.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>


Lexeme *current;
Lexeme *prev;
int legal = 1;


Lexeme *
advance()
{
    prev = current;
    current = lex();
    return prev;
}


int
check(char *type)
{
    return getLexemeType(current) == type;
}


Lexeme *
match(char *type)
{
    if (check(type)) return advance();
    legal = 0;
    printf("SYNTAX ERROR: expected %s, got %s - line %d\n",type,getLexemeType(current),getLine());
    printf("illegal\n");
    exit(0);
}


int
getLegal()
{
    return legal;
}


Lexeme *
cons(char *type, Lexeme *left, Lexeme *right)
{
    Lexeme *n = newLexeme(type);
    set_car(n,left);
    set_cdr(n,right);
    return n;
}


void
program()
{
    includes();
    if (defsPending()) defs();
    mainFunc();
}


void
defs()
{
    def();
    if (defsPending()) defs();
}


int
defsPending()
{
    return defPending();
}


void
def()
{
    if (varDefPending()) varDef();
    else funcDef();
}


int
defPending()
{
    return varDefPending() || funcDefPending();
}


void
includes()
{
    include();
    if (includesPending()) includes();
}


int
includesPending()
{
    return check(HASH);
}


void
include()
{
    match(HASH);
    match(INCLUDE);
    if (check(QUOTE))
    {
        match(QUOTE);
        match(ID);
        match(DOT);
        match(ID);
        match(QUOTE);
    }
    else
    {
        match(LESSTHAN);
        match(ID);
        match(DOT);
        match(ID);
        match(GREATERTHAN);
    }
}


void
funcDef()
{
    match(FUNCTION);
    match(ID);
    match(OPAREN);
    optParamList();
    match(CPAREN);
    block();
}


int
funcDefPending()
{
    return check(FUNCTION);
}


void
parameterList()
{
    match(VAR);
    match(ID);
    if (check(COMMA))
    {
        match(COMMA);
        parameterList();
    }
}


int
parameterListPending()
{
    return check(VAR);
}


void
optParamList()
{
    if (parameterListPending()) parameterList();
}


void
mainFunc()
{
    match(MAIN);
    match(OPAREN);
    optParamList();
    match(CPAREN);
    block();
}


void
varDef()
{
    match(VAR);
    match(ID);
    optInit();
    match(MONEY);
}


int
varDefPending()
{
    return check(VAR);
}


void
optInit()
{
    if (check(ASSIGN))
    {
        match(ASSIGN);
        expr();
    }
}


void
unary()
{
    if (check(MINUS))
    {
        match(MINUS);
        unary();
    }
    else if (check(INTEGER)) match(INTEGER);
    else if (check(REAL)) match(REAL);
    else if (check(STRING)) match(STRING);
    else match(ID);
}


int
unaryPending()
{
    return check(MINUS) || check(INTEGER) || check(REAL) || check(STRING) || check(ID);
}


void
oper()
{
    if (check(PLUS)) match(PLUS);
    else if (check(TIMES)) match(TIMES);
    else if (check(DIVIDES)) match(DIVIDES);
    else if (check(MINUS)) match(MINUS);
    else if (check(ASSIGN)) match(ASSIGN);
    else if (check(GREATERTHAN)) match(GREATERTHAN);
    else if (check(GREATERTHANOREQUAL)) match(GREATERTHANOREQUAL);
    else if (check(LESSTHAN)) match(LESSTHAN);
    else if (check(LESSTHANOREQUAL)) match(LESSTHANOREQUAL);
    else if (check(MOD)) match(MOD);
    else if (check(ANDAND)) match(ANDAND);
    else if (check(OROR)) match(OROR);
    else if (check(EQUALEQUAL)) match(EQUALEQUAL);
    else match(NOTEQUALS);
}


int
operPending()
{
    return check(PLUS) || check(TIMES) || check(DIVIDES) || check(MINUS)
        || check(ASSIGN) || check(GREATERTHAN) || check(GREATERTHANOREQUAL)
        || check(LESSTHAN) || check(LESSTHANOREQUAL) || check(NOTEQUALS)
        || check(MOD) || check(ANDAND) || check(OROR) || check(EQUALEQUAL);
}


void
expr()
{
    if (unaryPending())
    {
        unary();
        if (doubleSelfOpPending()) doubleSelfOp();
        else if (operPending())
        {
            oper();
            expr();
        }
    }
    else funcCall();
}


int
exprPending()
{
    return unaryPending() || funcCallPending();
}


void optExpr()
{
    if (exprPending()) expr();
}


void 
argList()
{
    expr();
    if (check(COMMA))
    {
        match(COMMA);
        expr();
    }
}


int
argListPending()
{
    return exprPending();
}


void
optArgList()
{
    if (argListPending()) argList();
}


void
funcCall()
{
    match(CALL);
    match(ID);
    match(OPAREN);
    optArgList();
    match(CPAREN);
}


int
funcCallPending()
{
    return check(CALL);
}


void
ifStatement()
{
    match(IF);
    match(OPAREN);
    expr();
    match(CPAREN);
    block();
    optElse();
}


int
ifStatementPending()
{
    return check(IF);
}


void
elseStatement()
{
    match(ELSE);
    if (ifStatementPending()) ifStatement();
    else block();
}


int
elseStatementPending()
{
    return check(ELSE);
}


void
optElse()
{
    if (elseStatementPending()) elseStatement();
}


void
whileLoop()
{
    match(WHILE);
    match(OPAREN);
    expr();
    match(CPAREN);
    block();
}


int
whileLoopPending()
{
    return check(WHILE);
}


void
returnStatement()
{
    match(RETURN);
    optExpr();
    match(MONEY);
}


int
returnStatementPending()
{
    return check(RETURN);
}


void
forLoop()
{
    match(FOR);
    match(OPAREN);
    match(VAR);
    match(ID);
    match(ASSIGN);
    match(INTEGER);
    match(SEMI);
    match(ID);
    checkOper();
    if (check(INTEGER))
    {
        match(INTEGER);
        match(SEMI);
        match(ID);
        selfOp();
        match(CPAREN);
        block();
    }
    else
    {
        match(ID);
        match(SEMI);
        match(ID);
        selfOp();
        match(CPAREN);
        block();
    }
}


int
forLoopPending()
{
    return check(FOR);
}


void
checkOper()
{
    if (check(GREATERTHAN)) match(GREATERTHAN);
    else if (check(GREATERTHAN)) match(GREATERTHANOREQUAL);
    else if (check(LESSTHAN)) match(LESSTHAN);
    else match(LESSTHANOREQUAL);
}


void
selfOp()
{
    if (check(PLUSEQUALS))
    {
        match(PLUSEQUALS);
        match(INTEGER);
    }
    else if (check(MINUSEQUALS))
    {
        match(MINUSEQUALS);
        match(INTEGER);
    }
    else if (check(TIMESEQUALS))
    {
        match(TIMESEQUALS);
        match(INTEGER);
    }
    else if (check(DIVIDESEQUALS))
    {
        match(DIVIDESEQUALS);
        match(INTEGER);
    }
    else doubleSelfOp();
}


void
doubleSelfOp()
{
    if (check(PLUSPLUS)) match(PLUSPLUS);
    else match(MINUSMINUS);
}


int
doubleSelfOpPending()
{
    return check(PLUSPLUS) || check(MINUSMINUS);
}


void
block()
{
    match(OBRACE);
    statements();
    match(CBRACE);
}


void
statements()
{
    statement();
    if (statementsPending()) statements();
}


int
statementsPending()
{
    return statementPending();
}


void
statement()
{
    if (exprPending())
    {
        expr();
        match(MONEY);
    }
    else if (varDefPending()) varDef();
    else if (funcDefPending()) funcDef();
    else if (ifStatementPending()) ifStatement();
    else if (whileLoopPending()) whileLoop();
    else if (forLoopPending()) forLoop();
    else if (returnStatementPending()) returnStatement();
    else funcCall();
}


int
statementPending()
{
    return exprPending() ||  varDefPending() || funcDefPending() || ifStatementPending()
        || whileLoopPending() || forLoopPending() || returnStatementPending()
        || funcCallPending();
}