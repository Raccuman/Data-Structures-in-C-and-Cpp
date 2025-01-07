/***

Catherine Bronte
cebronte 1969208
2024 Fall CSE101 PA2
A fun little descritpion of my program :3
***/

So this assignment was allright, it just didnt have a lot of flavor. And honestly, I prefer depth first search but whatever.

How I made it (the story of struggle and late nights): First I started with graph and right off the bat it went not super great. I ahve been struggling with my arrays and what not. Honestly I just prefer to deal with basic pointers, memory is HAAARD. Will I never not struggle with memore, who knows. So after going to office hours about that we were off to the races. The basic functions were pretty easy, and I just looked at the psudo code for get path and BFS. After, that, ran it through Graph client, did some debugging, edited the makefile here and there. Everything was good and nice and chill untill I ran it through the official tests. You know when something is broken so you change even the really easy sure fire stuff in hopes that it will start working? I did that. For whatever reason my helper print path function just kept printing the indices of the path length, not the path. I changes the grpah structure, the allocation, everything. No stone was unturned. And then I remembered my helper function I made to print the little text block and I found my problem. It was a stupid easy fir. After that It took me a minute and me talking to my friend to realize that DG stood for directed graph, and all I had to do was fix add arc, and now I am here. For the most part done, and having a slight headache.

HOW TO RUN PROGRAM:
FindPath.c - just do ./FindPath inputfile.txt outputfile.txt. and hit enter. Make sure the Input file is formatted like this
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

6 is the number of vertices, the 0 0 in the middle indecates that after defines the paths you want to find. The program finds the shortest paths between defined vertexes.

Graph.c - you cant run this, its inside the black box. The point of it along with Graph.h is to define the graph functions for FindPath. There is a helper function of mine in there as well caled myPath

List.c / List.h Also defines functions for Graph.c and you cannot touch these as well.

Makefile makes life alot easier and makes sure everything is all nice and compilled.

GraphTest.c is there to test some of by basic graph functions. Was more meant to see if things were crashing, and gdb purposes.