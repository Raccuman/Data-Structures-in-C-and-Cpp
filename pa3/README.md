/***
Catherine Bronte
cebronte 1969208
2024 Fall CSE101 PA3
A fun little descritpion of my program :3
***/

This was a pretty easy assignment, but I had some stupid mistakes.

Since this project uses a lot of PA3, the first step was to compleatly copy over PA2. Then I added my new functions to the .h file, and I went from easient to hardest. What I thought was the easiest ended up giving me the most problems at the end, and those were getDiscover and getFinish. I dont know what test 5 is, but it is failing on my directed and not directed graphs, and I cant figure out why it doesnt like my functions. They are compleatly functional when you see them, know that I probably fixed it 5 minutes to the due time, and didnt have enough time to update this doccument. I really tried. It works for everything else at lease. DFS and visit were fine, I decided to make time initialized in DFS, and passed into visit as an argument, then return it at the end of visit so it kept incrimenting through out. And then there was printing out the components in the correct order. That really took forever, but I ended up getting it. I turns out my first idea for implementing it out of 10 was the correct idea, I just didnt do it right. Took me about 2 hours before I triend it again and it worked. I really hope I can fix get discover and get finish before the due time, cause 20 / 40 makes me sad. I wish I knew what the problem was. Heck I even tried fixing every other function and NOTHING. Elusive problem for sure.

HOW TO RUN PROGRAM:
FindComponents.c - just do ./FindComponents inputfile.txt outputfile.txt. and hit enter. Make sure the Input file is formatted like this
6
1 2
1 3
2 4
2 5
2 6
3 4
4 5
5 6
0 0 ( It does not format correctly on Git lab)

6 is the number of vertices, 0 0 marks the end. The pairs are the edges in the graph. It will prind and adjacency list on the outfile as well a s alist of strongly connected components.

Graph.c - you cant run this, its inside the black box. The point of it along with Graph.h is to define the graph functions for FindComponents. There is a helper function of mine in there as well caled myPath

List.c / List.h Also defines functions for Graph.c and you cannot touch these as well.

Makefile makes life alot easier and makes sure everything is all nice and compilled.

GraphTest.c is there to test some of by basic graph functions. Was more meant to see if things were crashing, and gdb purposes.