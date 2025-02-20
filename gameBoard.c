//
// Created by Cathal on 16/04/2021.
//

/*
 * The board co-ordinates read as follows:
 * arr[y][x] with arr[0][0] being in the top left
 * x is the horizontals noted by a letter from 'a' to 'h' inclusive
 * y is the verticals noted by a number from '1' to '8' inclusive
*/

#include "gameBoard.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void printBoard(boardData gameBoard) {
    char **arr = gameBoard.board; // assign arr to point to the current board

    printf("\n");
    printf("%c  ", ' '); // print a blank buffer space to accommodate for the empty row number
    for (int i = 0; i < BOARDSIZE; ++i) {
        printf("  %c   ", 'a'+i);// print the column character
    }
    printf("\n");
    // print a Horizontal buffer
    printf("%c  ", ' '); // print a blank buffer space to accommodate for the empty row number
    for (int i = 0; i < BOARDSIZE; ++i) {
        printf("----- ");
    }
    printf("\n");

    for (int i = 0; i < BOARDSIZE; ++i) {
        printf("%d |", i+1); // print the row number
        for (int j = 0; j < BOARDSIZE; ++j) {
            printf("  %c  |",arr[i][j]);
        }
        printf("\n");

        // print a Horizontal buffer
        printf("%c  ", ' '); // print a blank buffer space to accommodate for the empty row number
        for (int i = 0; i < BOARDSIZE; ++i) {
            printf("----- ");
        }
        printf("\n");
    }
}

char ** initialiseBoard() {
    /*
     * Allocate a block of memory for pointers to the beginning of each row and all the cells
     * In this case (8 + (8 * 8))
     * The first n(8) elements are pointers to the first element of each row
     * The remaining elements are the actual data
     */

    char **arr;
    char *ptr; // points to the first element of the first row of the 2d array
    int len; // the size of the memory block that needs to be allocated

    len = BOARDSIZE * sizeof(char *); // first 8 spaces for pointers to char
    len += (BOARDSIZE * BOARDSIZE) * sizeof(char); // remaining 64(8*8) spaces to store all the char

    // allocate block of memory
    arr = (char **) malloc(len); // allocate the memory

    // check if there was an issue allocating the memory
    if (arr == NULL){
        printf("Error allocating Memory");
        exit(3);
    }else{
        // set the first BOARDSIZE (8) elements to pointers, pointing to locations in that block of memory
        ptr = (char *) (arr + BOARDSIZE); // set ptr to the location of the first element
        for (int i = 0; i < BOARDSIZE; ++i) {
            arr[i] = ptr + (BOARDSIZE * i); // set each index pointing to the corresponding location in the 2d array
        }

        // populate the board with blank spaces '\0'
        for (int i = 0; i < BOARDSIZE; ++i) {
            for (int j = 0; j < BOARDSIZE; ++j) {
                arr[i][j] = '\0';
            }
        }

        // add the 4 starting positions
        // white starts at d4 and e5
        // removed manual changing to use custom function
        //arr[4-1][4-1] = '1'; // d4
        //arr[5-1][5-1] = '2'; // e5
        changeCell(arr,'d',4,'w');
        changeCell(arr,'e',5,'w');
        // black starts at d5 and e4
        //arr[5-1][4-1] = '3'; // d5
        //arr[4-1][5-1] = '4'; // e4
        changeCell(arr,'d',5,'b');
        changeCell(arr,'e',4,'b');
    }


    return arr;
}

void changeCell(char **arr, char xPos, int yPos, char colour) {
    int x,y;
    x = xPos - 'a'; // maps board column to array indexes
    y = yPos - 1; // maps board rows to array indexes

    arr[y][x] = colour;
}

void saveResults(boardData gameBoard) {
    const char *filePath = "othello-results.txt";
    FILE *fp;
    time_t rawtime;
    struct tm *myTime;
    char timeBuffer[80]; // a buffer to store 80 character from a stringed time and date

    char *ptr1 = NULL, *ptr2 = NULL; // pointers that point to the two strings
    char strWhite[] = "White";
    char strBlack[] = "Black";


    // get the time and format it accordingly
    time(&rawtime);
    myTime = localtime(&rawtime);
    strftime(timeBuffer,80,"%d/%m/%Y - %I:%M%p", myTime);

    // associate the correct colour to the correct player
    if (gameBoard.player1.colour == 'w'){
        ptr1 = strWhite;
        ptr2 = strBlack;
    } else{
        ptr1 = strBlack;
        ptr2 = strWhite;
    }

    fp = fopen(filePath, "a");

    if(gameBoard.player1.score > gameBoard.player2.score){
        // player 1 wins
        fprintf(fp,
                "|%s| %s won. Final Score: %s (%s) %d:%d %s (%s)\n",
                timeBuffer,
                gameBoard.player1.name,
                gameBoard.player1.name,
                ptr1,
                gameBoard.player1.score,
                gameBoard.player2.score,
                gameBoard.player2.name,
                ptr2);
    } else if(gameBoard.player2.score > gameBoard.player1.score){
        // player 2 wins
        fprintf(fp,
                "|%s| %s won. Final Score: %s (%s) %d:%d %s (%s)\n",
                timeBuffer,
                gameBoard.player2.name,
                gameBoard.player1.name,
                ptr1,
                gameBoard.player1.score,
                gameBoard.player2.score,
                gameBoard.player2.name,
                ptr2);
    } else {
        // draw game
        fprintf(fp,
                "|%s| Draw. Final Score: %s (%s) %d:%d %s (%s)\n",
                timeBuffer,
                gameBoard.player1.name,
                ptr1,
                gameBoard.player1.score,
                gameBoard.player2.score,
                gameBoard.player2.name,
                ptr2);
    }

    fclose(fp);
}

