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

Print with 'call print()'

============================
To run Lexer using makefile commands:

  make : compiles scanner executable
  
  make test1 : runs recognizer on test1.txt, illegal
  make test2 : runs recognizer on test2.txt, illegal
  make test3 : runs recognizer on test3.txt, legal
  make test4 : runs recognizer on test4.txt, legal
  make test5 : runs recognizer on test5.txt, illegal
  
  # for the sake of allowing the make run command to run all the way through, I used exit code 0 when reading a Syntax Error. This will be changed to a non zero exit code after testing
  make run : compiles recognizer executable and executes all 5 test cases
  
  make clean : gets rid of all .o files and scanner executable
  
  
============================

