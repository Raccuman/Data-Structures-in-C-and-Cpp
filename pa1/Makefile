
#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 1
#
# make                   makes Lex
# make ListClient        makes ListClient
# make clean             removes all binaries
# make checkClient       checks ListClient for memory errors
# make checkLex          checks Lex for memory errors
#------------------------------------------------------------------------------

## dont forget to delete -g at the end
Lex : Lex.o List.o
	gcc -g -std=c17 -Wall -o Lex Lex.o List.o

Lex.o : Lex.c List.h
	gcc -g -std=c17 -Wall -c Lex.c

ListClient: ListClient.o List.o
	gcc -g -std=c17 -Wall -o ListClient ListClient.o List.o

ListClient.o : ListClient.c List.h
	gcc -g -std=c17 -Wall -c ListClient.c

List.o : List.c List.h
	gcc -g -std=c17 -Wall -c List.c

ListTest : ListTest.o List.o
	gcc -std=c17 -Wall -o ListTest ListTest.o List.o 

ListTest.o : List.h ListTest.c
	gcc -std=c17 -Wall -c ListTest.c

clean :
	rm -f Lex ListClient Lex.o ListClient.o List.o ListTest ListTest.o

checkClient : 
	valgrind --leak-check=full ListClient

checkLex :
	valgrind --leak-check=full Lex input.txt output.txt
	