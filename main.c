/*
    Assignment 2

    Written by: Cathal Poon
    S/N: 20343243

    A C program that manages a game of Othello (Reversi) between two players

    For Module COMP10050
    Assignment 2
*/

#include <stdio.h>
#include <stdlib.h>
#include "gameLogic.h"
//#include "gameBoard.h"
//#include "players.h"
#define BOARDSIZE 8


int main() {
    boardData myBoard; // struct storing the game board and play structs
    /*
     * The board co-ordinates read as follows:
     * arr[y][x] with arr[0][0] being in the top left
     * x is the horizontals noted by a letter from 'a' to 'h' inclusive
     * y is the verticals noted by a number from '1' to '8' inclusive
     */

    myBoard.board = initialiseBoard();
    initPlayers(&(myBoard.player1),&(myBoard.player2)); // initialise the players

    printPlayers(&(myBoard.player1),&(myBoard.player2));
    printBoard(&myBoard);

    for (int i = 0; i < BOARDSIZE; ++i) {
        for (int j = 0; j < BOARDSIZE; ++j) {
            move(&myBoard,myBoard.player1);
            printBoard(&myBoard);
        }
    }


    free(myBoard.board); //free the memory allocated for the board
    return 0;
}
