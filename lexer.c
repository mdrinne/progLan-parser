/*
 * Matthew Rinne
 * lexical-analyzer.c
 * cs403 Programming Languages
 */


#include "lexer.h"
#include "types.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>


FILE *fp;
char pushbackChar;
int charHasBeenPushed = 0;
int line = 1;
int success;


void
skipComment()
{
    char ch = readChar(fp);
    while (ch != '?')
    {
        ch = readChar(fp);
        if (ch == 10)
        {
            line++;
        }
    }
}


int
isWhiteSpace(char ch)
{
    if (ch == 10)
    {
        line++;
        return 1;
    }
    else if (ch >= 64) return 0;
    else if (ch == 0) return 0;
    else if (ch >= 33 && ch <= 62) return 0;
    else if (ch == '?')
    {
        skipComment();
        return 1;
    }
    else 
    {
        return 1;
    }
}


void
skipWhiteSpace()
{
    char ch = readChar(fp);
    while(isWhiteSpace(ch))
    {
            ch = readChar(fp);
    }
    pushback(ch);
    return;
}


void
pushback(char ch)
{
    if (charHasBeenPushed)
    {
        printf("FATAL ERROR: too many pushbacks\n");
        exit(1);
    }
    charHasBeenPushed = 1;
    pushbackChar = ch;
}


char
readChar()
{
    if (charHasBeenPushed)
    {
        charHasBeenPushed = 0;
        return pushbackChar;
    }
    else if (feof(fp)) return 0;
    else
    {
        char ch = fgetc(fp);
        return ch;
    }
}


double
toReal(char *buf)
{
    return strtod(buf, NULL);
}


int
toInt(char *buf)
{
    return atoi(buf);
}


Lexeme *
lexNumber()
{
    int len = 16;
    int index = 0;
    int real = 0;
    char *buffer = malloc(sizeof(char) * len+1);
    char ch;
    ch = readChar();
    while (ch != EOF && (isdigit(ch) || ch == '.'))
    {
        if (index == len)
        {
            len *= 2;
            buffer = realloc(buffer,sizeof(char) * len+1);
        }
        buffer[index] = ch;
        index++;
        buffer[index] = '\0';
        if (ch == '.' && real)
        {
            printf("FATAL ERROR: BAD_NUMBER, too many \'.\' - LINE %d\n",line);
            exit(1);
        }
        if (ch == '.') real = 1;
        ch = readChar();
    }
    pushback(ch);
    if (real) return newLexemeReal(toReal(buffer));
    else return newLexemeInt(toInt(buffer));
}


Lexeme *
lexVarOrKeyword()
{
    int len = 16;
    int index = 0;
    char *buffer = malloc(sizeof(char) * len+1);
    char ch;
    ch = readChar();
    while (ch != EOF && (isalpha(ch) || isdigit(ch)))
    {
        if (index == len)
        {
            len *= 2;
            buffer = realloc(buffer,sizeof(char) * len+1);
        }
        buffer[index] = ch;
        index++;
        buffer[index] = '\0';
        ch = readChar();
    }
    pushback(ch);
    if (strcmp(buffer, "if") == 0) return newLexeme(IF);
    else if (strcmp(buffer, "else") == 0) return newLexeme(ELSE);
    else if (strcmp(buffer, "while") == 0) return newLexeme(WHILE);
    else if (strcmp(buffer, "main") == 0) return newLexeme(MAIN);
    else if (strcmp(buffer, "include") == 0) return newLexeme(INCLUDE);
    else if (strcmp(buffer, "func") == 0) return newLexeme(FUNCTION);
    else if (strcmp(buffer, "return") == 0) return newLexeme(RETURN);
    else if (strcmp(buffer, "var") == 0) return newLexeme(VAR);
    else if (strcmp(buffer, "for") == 0) return newLexeme(FOR);
    else if (strcmp(buffer, "print") == 0) return newLexeme(PRINT);
    else return newLexemeVar(buffer);
}


Lexeme *
lexString()
{
    int len = 16;
    int index = 0;
    char *buffer = malloc(sizeof(char) * len+1);
    char ch;
    ch = readChar();
    char prev;
    while (ch != EOF && (ch != 39 || (ch == 39 && prev == 92)))
    {
        if (index == len)
        {
            len *= 2;
            buffer = realloc(buffer, sizeof(char) * len+1);
        }
        buffer[index] = ch;
        index++;
        buffer[index] = '\0';
        prev = ch;
        ch = readChar();
    }
    return newLexemeString(buffer);
}


Lexeme *
lex()
{
    char ch;
    skipWhiteSpace();
    ch = readChar();
    
    switch(ch)
    {
        case '{': return newLexeme(OBRACE);
        case '}': return newLexeme(CBRACE);
        case '(': return newLexeme(OPAREN);
        case ')': return newLexeme(CPAREN);
        case '[': return newLexeme(OBRACKET);
        case ']': return newLexeme(CBRACKET);
        case ',': return newLexeme(COMMA);
        case '*': return newLexeme(TIMES);
        case '/': return newLexeme(DIVIDES);
        case ';': return newLexeme(SEMI);
        case '$': return newLexeme(MONEY);
        case '%': return newLexeme(MOD);
        case '@': return newLexeme(AT);
        case '!': return newLexeme(NOT);
        case '.': return newLexeme(DOT);
        case '#': return newLexeme(HASH);
        case '?': return newLexeme(QUESTION);
        case ':': return newLexeme(COLON);
        case '"': return newLexeme(QUOTE);

        default:
            if (ch == '&')
            {
                ch = readChar();
                if (ch == '&') return newLexeme(ANDAND);
                else
                {
                    pushback(ch);
                    return newLexeme(AMPERSAND);
                }
            }
            else if (ch == '|')
            {
                ch = readChar();
                if (ch == '|') return newLexeme(OROR);
                else
                {
                    pushback(ch);
                    return newLexeme(BAR);
                }
            }
            else if (ch == '<')
            {
                ch = readChar();
                if (ch == '=') return newLexeme(LESSTHANOREQUAL);
                else
                {
                    pushback(ch);
                    return newLexeme(LESSTHAN);
                }
            }
            else if (ch == '>')
            {
                ch = readChar();
                if (ch == '=') return newLexeme(GREATERTHANOREQUAL);
                else
                {
                    pushback(ch);
                    return newLexeme(GREATERTHAN);
                }
            }
            else if (ch == '+')
            {
                ch = readChar();
                if (ch == '+') return newLexeme(PLUSPLUS);
                else
                {
                    pushback(ch);
                    return newLexeme(PLUS);
                }
            }
            else if (ch == '-')
            {
                ch = readChar();
                if (ch == '-') return newLexeme(MINUSMINUS);
                else
                {
                    pushback(ch);
                    return newLexeme(MINUS);
                }
            }
            else if (ch == '=')
            {
                ch = readChar();
                if (ch == '=') return newLexeme(EQUALEQUAL);
                else
                {
                    pushback(ch);
                    return newLexeme(ASSIGN);
                }
            }
            else if (isdigit(ch))
            {
                pushback(ch);
                return lexNumber();
            }
            else if (isalpha(ch))
            {
                pushback(ch);
                return lexVarOrKeyword();
            }
            else if (ch == '\'') return lexString();
            else if (ch == 0) return newLexeme(END_OF_FILE);
            else
            {
                printf("FATAL ERROR: UNKOWN CHARACTER - LINE %d\n",line);
                exit(1);
            }
    }
}


void
getFile(FILE *f)
{
    fp = f;
}