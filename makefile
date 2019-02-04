LOPTS = -Wall -Wextra -std=c99
OBJS = lexer.o lexeme.o types.o scanner.o parser.o recognizer.o

make : recognizer scanner

run : recognizer test1 test2 test3 test4 test5

recognizer:
	gcc $(LOPTS) -c recognizer.c lexer.c lexeme.c types.c parser.c
	gcc $(LOPTS) recognizer.c lexer.o lexeme.o types.o parser.o -o recognizer

scanner :
	gcc $(LOPTS) -c scanner.c lexer.c lexeme.c types.c
	gcc $(LOPTS) scanner.c lexer.o lexeme.o types.o -o scanner

test1 :
	recognizer test1.txt

test2 :
	recognizer test2.txt

test3 :
	recognizer test3.txt

test4 :
	recognizer test4.txt

test5 :
	recognizer test5.txt

clean :
	rm -f $(OBJS) scanner recognizer