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
#define BOARDSIZE 8

void printBoard(boardData *gameBoard) {
    char **arr = gameBoard->board; // assign arr to point to the current board

    printf("\n");
    printf("%c", ' ');
    for (int i = 0; i < BOARDSIZE; ++i) {
        printf("%3c", 'a'+i);
    }
    printf("\n");
    for (int i = 0; i < BOARDSIZE; ++i) {
        printf("%d", i+1);
        for (int j = 0; j < BOARDSIZE; ++j) {
            printf("%3c",arr[i][j]);
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

    // allocate block of memory
    arr = (char **) malloc((BOARDSIZE + (BOARDSIZE * BOARDSIZE)) * sizeof(char));

    // set the first BOARDSIZE (8) elements to pointers, pointing to locations in that block of memory
    ptr = (char *) (arr + BOARDSIZE); // set ptr to the location of the first element
    for (int i = 0; i < BOARDSIZE; ++i) {
        arr[i] = ptr + (BOARDSIZE * i); // set each index pointing to the corresponding location in the 2d array
    }

    // populate the board with blank spaces '*'
    for (int i = 0; i < BOARDSIZE; ++i) {
        for (int j = 0; j < BOARDSIZE; ++j) {
            arr[i][j] = '*';
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

    return arr;
}

void changeCell(char **arr, char xPos, int yPos, char colour) {
    int x,y;
    x = xPos - 'a'; // maps board column to array indexs
    y = yPos - 1; // maps board rows to array indexs

    arr[y][x] = colour;
}

