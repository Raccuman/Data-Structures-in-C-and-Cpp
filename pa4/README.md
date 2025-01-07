/***
Catherine Bronte
cebronte 1969208
2024 Fall CSE101 PA4
A fun little descritpion of my program :3
***/

Not gonna lie, this was rough. It should have been easy, but it was not

First off, my makefile was not working. I think this set me back by about 3 days. I could write the functions all fine and dandy but I could not test them. Guess what the sollution was? It said test where is should have said client. That was it. And then is was easy street for a while, everything was working, I got matrixClient going, the Sparse page was easy, things were good. And then on the last day I put it through the main tests. Man, my program had issues. I keep getting this one particular memory leak with change entry. I have tried fixing this thing for 5 hours. I think it might be a machine problem at this point but I am too tired to care. If either sum or change entry leaks on your end, please have mercy. Lesson of the day, no more waiting. The PA's are real now.



HOW TO RUN PROGRAM:
Sparse.c - just do ./Sparse inputfile.txt outputfile.txt. and hit enter. Make sure the Input file is formatted like this
3 9 5

1 1 1.0
1 2 2.0
1 3 3.0
2 1 4.0
2 2 5.0
2 3 6.0
3 1 7.0
3 2 8.0
3 3 9.0

1 1 1.0
1 3 1.0
3 1 1.0
3 2 1.0
3 3 1.0
( It does not format correctly on Git lab)

3 is the size of the graph, 9 is the number of elements in the first graph, 5 is the number of elements in the second graph   

Matrix.c / Matrix.h - you cant run this, its inside the black box. The point of it along with Graph.h is to define the graph functions for FindComponents. There is a helper function of mine in there as well caled myPath

List.c / List.h Also defines functions for Graph.c and you cannot touch these as well.

Makefile makes life alot easier and makes sure everything is all nice and compilled.

MatrixTest.c is there to test some of by basic Matrix functions. Was more meant to see if things were crashing, and gdb purposes.

ListTest.c is for testing my updated list functions cause I had to change my format from int to void* for this assignment.