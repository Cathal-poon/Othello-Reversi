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
#define BOARDSIZE 8

void printBoard(char (*arr)[BOARDSIZE]) {
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

void initialiseBoard(char (*arr)[8]) {
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


}

void changeCell(char (*arr)[8], char xPos, int yPos, char colour) {
    int x,y;
    x = xPos - 'a'; // maps board column to array indexs
    y = yPos - 1; // maps board rows to array indexs

    arr[y][x] = colour;
}

