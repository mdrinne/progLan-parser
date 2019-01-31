LOPTS = -Wall -Wextra -std=c99
OBJS = lexer.o lexeme.o types.o scanner.o

make : scanner

run : scanner test1 test2 test3 test4 test5

scanner :
	gcc $(LOPTS) -c scanner.c lexer.c lexeme.c types.c
	gcc $(LOPTS) scanner.c lexer.o lexeme.o types.o -o scanner

test1 :
	scanner test1.txt

test2 :
	scanner test2.txt

test3 :
	scanner test3.txt

test4 :
	scanner test4.txt

test5 :
	scanner test5.txt

clean :
	rm -f $(OBJS) scanner