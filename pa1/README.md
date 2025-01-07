/***
* Catherine Bronte 
* cebronte 1969208
* 2024 Fall CSE101 PA1
* Lex.c
* A fun little descritpion of my program :3
***/

Hello hello, this is the first read me I have ever made! I am not quite sure how sophisticated this needs to be so I will start with this

I know we were supposed to write our own tests, but I honestly like using print statements and GDB. You know, single stepping through the entire program and what not. So if my tests are not that fancy, that it why. I am testing, just not though code.

This program is all about reading in a file of lines, sorting each line alphabetically, and putting the new sorted list in a different file. BUT, the catch is that I had to make a whole doubly linked list ADT that stores integers, and it had a lot of different functions (some just for later assignments)

Step 1 of the project was making the list ADT. I did the bad way and made every single function, THEN tested it. I dont know, I like debugging all at once. You see a stack of problems get smaller and smaller. PrintList was particularly difficult as my origional method had to be scrapped since it deleted the origional list in the process. Delete was also a bit difficult since when deleting a doubly linked list there are a lot of things to move around. Lots of GDB was involved.

Then I messed with the Makefile to get things working, ended up being pretty simple.

After that I built Lex, which was way more difficult that I thought it would be. I totally forgot how to do char and string arrays, so I had to spend an hour figuring out how to put the lines into a string array. But after that bit everything went pretty smoothly. I triend making a bubble sort algorithm at first, but then I realized my mistake and switched to insert sort. Honestly not that bad to program. Then I freed everything and the program was done. 

HOW TO RUN PROGRAM:
before both of these make sure your Make file is up and running. Do make clean and make /programname/

Lex - type ./Lex input.txt output.txt and hit enter
input.txt has the lines you want alphabetised, and output.txt will receive the sorted lines in correct order.

ListTest - type ./ListTest 
this test is just to check for crashes, so it doesnt really do much. You shouldent get anything back






