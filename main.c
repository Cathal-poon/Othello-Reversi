/*
    Assignment 2

    Written by: Cathal Poon
    S/N: 20343243

    A C program that manages a game of Othello (Reversi) between two players

    For Module COMP10050
    Assignment 2
*/

#include <stdio.h>
#include "gameBoard.h"
#include "players.h"
#define BOARDSIZE 8


int main() {
    char myBoard[BOARDSIZE][BOARDSIZE];
    /*
     * The board co-ordinates read as follows:
     * arr[y][x] with arr[0][0] being in the top left
     * x is the horizontals noted by a letter from 'a' to 'h' inclusive
     * y is the verticals noted by a number from '1' to '8' inclusive
     */

    /*
    player player1= {"John",'b',2};
    player1.name = getName();
    printf("%s",player1.name);
    */

    initialiseBoard(myBoard);
    printBoard(myBoard);
    return 0;
}
