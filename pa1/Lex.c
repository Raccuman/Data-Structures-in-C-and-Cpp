/***
* Catherine Bronte 
* cebronte 1969208
* 2024 Fall CSE101 PA1
* Lex.c
* runs the sorting algorithm and deals with files
***/

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include <string.h>
#include "List.h"

int main (int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Bad! you didnt input an in file AND an out file");
        exit(1);
    }

    FILE* in_file = fopen(argv[1], "r");
    if (in_file == NULL) {
        fprintf(stderr, "your input file didnt open correctly, that sounds like a you problem, BAD!");
        exit(1);
    }

//////////////////////////////////////////////// starting to mess with line read in ///////////////////////////////////////
    int lines_in_file = 0;
    char ch = 'A';
    int big_sentence = 0;
    int compare = 0;
    while(!feof(in_file)) {
        ch = fgetc(in_file);
        big_sentence += 1;
        if(ch == '\n')
            {
                lines_in_file+= 1;
                if (compare < big_sentence) {
                    compare = big_sentence;
                }
                big_sentence = 0;
            }
        }

    compare += 1;

    // resets fgetc to the begining
    fseek(in_file, 0, SEEK_SET);

    ////////////////////////////////////////// Time to get funky /////////////////////////////////////////////////

    // Allocate memory for storing lines
    char **stringArray = malloc(lines_in_file * sizeof(char *));

    char buffer[compare];  // Buffer to hold each line temporarily
    int lineCount = 0;

    // Read each line from the file and store it in the array
    while (fgets(buffer, compare, in_file)) {
        // Remove the newline character from the line if present
        buffer[strcspn(buffer, "\n")] = '\0';

        // Allocate memory for the current line and store it, might have issues with the +1, remove if difficult
        stringArray[lineCount] = malloc(strlen(buffer) + 1);

        strcpy(stringArray[lineCount], buffer);  // Copying the line into the array
        lineCount++;
    }

    fclose(in_file); 

///////////////////////////////////////////////// end of line read in junk, its all in stringArray ///////////////////////

    /* Print the lines stored in the array
    printf("Lines from the file:\n");
    for (int i = 0; i < lineCount; i++) {
        printf("%s\n", stringArray[i]);
        free(stringArray[i]);  // Free the memory allocated for each line
    }
*/
/////////////////////////////////////////////////////// sorting junk ///////////////////////////////////////////
    // you need to pre figure out what goes in in which order before you do it, BUBBLE SORT
    List final = newList();
    int checker = 0;
    moveFront(final);
    append(final, 0);
    for (int k = 1; k < lineCount; k += 1) {
        moveFront(final);
        checker = 0;
        while (checker < length(final)) {
            if (strcmp(stringArray[k], stringArray[get(final)]) <= 0) {
                insertBefore(final, k);
                break;
            }
            moveNext(final);
            checker++;
        }
        if (length(final) == checker) {
            append(final, k);
        }
        }

    

///////////////////////////////////// writing out and closing up ////////////////////////////////////////////////////

    FILE* out_file = fopen(argv[2], "w");
    if (out_file == NULL) {
        fprintf(stderr, "your output file didnt open correctly, that sounds like a you problem, BAD!");
        exit(1);
    }

    moveFront(final);
    for (int q = 0; q < length(final); q++) {
        fprintf(out_file, "%s\n", stringArray[get(final)]);
        moveNext(final);
    }
    fclose(out_file); 

    for (int i = 0; i < lineCount; i++) {
    free(stringArray[i]);  
}

    free(stringArray);  // Free the memory allocated for the array
    freeList(&final);
    return 0;


}

