//
// Created by Cathal on 15/05/2021.
//

#include "gameLogic.h"
#include <stdio.h>

// function to check every cardinal direction
int N(boardData * gameBoard, char x, int y, char colour);
int NE(boardData * gameBoard, char x, int y, char colour);
int E(boardData * gameBoard, char x, int y, char colour);
int SE(boardData * gameBoard, char x, int y, char colour);
int S(boardData * gameBoard, char x, int y, char colour);
int SW(boardData * gameBoard, char x, int y, char colour);
int W(boardData * gameBoard, char x, int y, char colour);
int NW(boardData * gameBoard, char x, int y, char colour);

int inLimits(char x, int y);
/*
 * Check if a location is inside the game board. return 1 if yes and 0 if no
 */

int moveCheck(boardData * gameBoard, char x, int y, char colour);
/*
 * Check if a given move is valid. return 1 if yes and 0 if no
 */

int move(boardData *gameBoard, player currentPlayer) {
    char myX;
    int myY;
    int repeat = 1;



    do {
        fflush(stdin);
        printf("\nPlease enter a Location on the board, letter then number or 'p' for pass:");
        myX = getchar(); // read in the letter

        // if the character is uppercase convert it to a lowercase
        if (myX >= 'A' && myX <= 'Y'){
            myX -= 'A';
            myX += 'a';
        }

        // if a pass is requested then skip everything and go to the next player
        if (myX == 'p'){
            break;
        }

        myY = getchar(); // read in the digit
        myY -= '0'; // convert it from an ascii value to an integer

        // check if the input is valid
        if(inLimits(myX, myY)){
            // check if the move is valid
            changeCell(gameBoard->board, myX, myY, /*currentPlayer.colour*/ 'T');
            repeat = 0;
        }

    } while (repeat);

    return repeat;
}

int inLimits(char xPos, int yPos) {
    int myBool = 0;
    int x,y;

    x = xPos - 'a';
    y = yPos - 1;

    if (
            x >= 0          &&
            x < BOARDSIZE  &&
            y >= 0          &&
            y < BOARDSIZE
            ){
        myBool = 1;
    }

        return myBool;
}
