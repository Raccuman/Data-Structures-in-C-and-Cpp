/***
* Catherine Bronte 
* cebronte 1969208
* 2024 Fall CSE101 PA1
* Lex.c
* runs my basic tests on the program
***/

#include "List.h"


int main (void) {
    List my_list = newList();

    FILE *fp = fopen("output.txt", "w");

    moveFront(my_list);

    //adding things to list, should look like [3, 5, 8]
    append(my_list, 5);
    append(my_list, 8);
    prepend(my_list, 3);
    append(my_list, 6);

    printList(fp, my_list);
    printList(fp, my_list);

    freeList(&my_list);

    fclose(fp);
    return 0;
}



