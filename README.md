My Programming Language     //name still in the works
Matt Rinne
cs403 Programming Languagues

============================
Very similar to c, with slight differences

Includes at the top, just like in c

Main function, like c as well

variable definition: type is not specified, use var
  var x = 123
  var str = 'string'
  var temp
  
Statements end with a '$'

Strings can be added together with '+'

Will support arrays down the road, will have built in functions

Print with 'print()'

============================
To run Lexer using makefile commands:

  make : compiles scanner executable
  
  make test1 : runs scanner on test1.txt
  make test2 : runs scanner on test2.txt
  make test3 : runs scanner on test3.txt
  make test4 : runs scanner on test4.txt
  make test5 : runs scanner on test5.txt
  
  make run : compiles scanner executable and executes all 5 test cases
  
  make clean : gets rid of all .o files and scanner executable
  
  
============================
Assignment:
Tasked with creating our own programming language.
Starting with the grammer, had to create grammar rules in Backus Naur Form.
Next step was lexical analysis, in which we create lexemes to store token types so that we can check our grammar come parsing time.
