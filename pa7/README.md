/***
*Catherine Bronte
*cebronte 1969208
*2024 Fall CSE101 PA7
*README.md
*this is where the Dictionary classes and functions get defined
***/

Man, this assignment was pretty nice. A good break from all of the crazyness that has been the past few assignments. Nothing really noteable here, Order was pretty easy to make, and I found a really cool trick for debugging. If I hijak the client file and put the copy over the autograder tests indivigually, it make using GDB waaay easier. I think it saved me an hour figuring that one out.

How to use:

Order.cpp -> just do ./Order infile.txt outfile.txt   and have your infile be a bunch of words, each on their own indivigual line. The output will be a dictionary representation of it

Dictionary.cpp / Dictionary.h -> inside the black box, not meant for users to touch. This is were all of the dictionary functions are defined and written so Order works

DictionaryTest.cpp -> meant for my own testing purposes, no touch!

Makefile -> makes the files, in order

README.md -> a lovely little description of my code that you are reading right now.

