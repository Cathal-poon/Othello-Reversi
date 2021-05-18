/*
    Assignment 2

    Written by: Cathal Poon
    S/N: 20343243

    A C program that manages a game of Othello (Reversi) between two players

    For Module COMP10050
    Assignment 2
*/

#include <stdlib.h>
#include "gameLogic.h"
//#include "gameBoard.h"
//#include "players.h"



int main() {
    int gameStatus = 1;
    int passCounter = 0, passBuffer;
    player * firstPlayer, * secondPlayer;
    boardData myBoard; // struct storing the game board and play structs
    /*
     * The board co-ordinates read as follows:
     * arr[y][x] with arr[0][0] being in the top left
     * x is the horizontals noted by a letter from 'a' to 'h' inclusive
     * y is the verticals noted by a number from '1' to '8' inclusive
     */

    myBoard.board = initialiseBoard();
    initPlayers(&(myBoard.player1),&(myBoard.player2)); // initialise the players

    if (myBoard.player1.colour == 'b'){
        firstPlayer = &myBoard.player1;
        secondPlayer = &myBoard.player2;
    }else {
        firstPlayer = &myBoard.player2;
        secondPlayer = &myBoard.player1;
    }

    do {
        passBuffer = playerTurn(&myBoard,*firstPlayer);
        passCounter = (passCounter * passBuffer) + passBuffer;

        if(passCounter > 1){
            gameStatus = 0;
            break;
        }

        passBuffer = playerTurn(&myBoard,*secondPlayer);
        passCounter = (passCounter * passBuffer) + passBuffer;

        if(passCounter > 1){
            gameStatus = 0;
            break;
        }
    } while (gameStatus);

    // game has finished

    printBoard(myBoard);

    printEnding(myBoard);

    free(myBoard.board); //free the memory allocated for the board
    return 0;
}
