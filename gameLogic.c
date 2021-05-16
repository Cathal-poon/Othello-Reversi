//
// Created by Cathal on 15/05/2021.
//

#include "gameLogic.h"
#include <stdio.h>

// function to check every cardinal direction
short int N(boardData * gameBoard, char x, int y, char colour, int n);
short int NE(boardData * gameBoard, char x, int y, char colour, int n);
short int E(boardData * gameBoard, char x, int y, char colour, int n);
short int SE(boardData * gameBoard, char x, int y, char colour, int n);
short int S(boardData * gameBoard, char x, int y, char colour, int n);
short int SW(boardData * gameBoard, char x, int y, char colour, int n);
short int W(boardData * gameBoard, char x, int y, char colour, int n);
short int NW(boardData * gameBoard, char x, int y, char colour, int n);

int inLimits(char x, int y);
/*
 * Check if a location is inside the game board. return 1 if yes and 0 if no
 */

unsigned short int moveCheck(boardData * gameBoard, char x, int y, char colour);
/*
 * Check if a given move is valid.
 * Returns 0 if no
 * or a number with all the possible moves encoded in binary in the form
 * The first 8 bits represent all the cardinal direction
 * N    - 2^7 [128]
 * NE   - 2^6 [64]
 * E    - 2^5 [32]
 * SE   - 2^4 [16]
 * S    - 2^3 [8]
 * SW   - 2^2 [4]
 * W    - 2^1 [2]
 * NW   - 2^0 [1]
 * 1 indicating it's a valid move
 * 0 indicating invalid
 * if all directions are valid then it will return 255
 * if only N is valid then it will return 128
 *
 */

int doMove(boardData *gameBoard, player currentPlayer) {
    char myX;
    int myY;
    int repeat = 1;
    int valid;


    do {
        fflush(stdin);
        printf("\nPlease enter a valid move location on the board, letter then number; or enter 'p' for pass:");
        myX = (char) getchar(); // read in the letter

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
            valid = moveCheck(gameBoard, myX, myY, currentPlayer.colour);
            if (valid){
                changeCell(gameBoard->board, myX, myY, currentPlayer.colour);
                repeat = 0;
            }
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

unsigned short int moveCheck(boardData *gameBoard, char xPos, int yPos, char colour) {
    unsigned short int total = 0;
    /*
     * Total encodes all possible moves and store them bitwise
     * N    - 2^7 [128]
     * NE   - 2^6 [64]
     * E    - 2^5 [32]
     * SE   - 2^4 [16]
     * S    - 2^3 [8]
     * SW   - 2^2 [4]
     * W    - 2^1 [2]
     * NW   - 2^0 [1]
     * 1 indicating it's a valid move
     * 0 indicating invalid
     * if all directions are valid then it will return 255
     * if only N is valid then it will return 128
     * if S and W are valid it will return 6
     */
    int x,y;

    x = xPos - 'a';
    y = yPos - 1;

    // check if it's an empty location
    if (gameBoard->board[y][x] == '*'){
        // check all directions to see if there is a valid move
        total += N(gameBoard,xPos,yPos,colour,1); // add the return value to the total (should be 0 or 1)
        total <<= 1;
/*
        total += NE(gameBoard,xPos,yPos,colour,0);
        total <<= 1;

        total += E(gameBoard,xPos,yPos,colour,0);
        total <<= 1;

        total += SE(gameBoard,xPos,yPos,colour,0);
        total <<= 1;

        total += S(gameBoard,xPos,yPos,colour,0);
        total <<= 1;

        total += SW(gameBoard,xPos,yPos,colour,0);
        total <<= 1;

        total += W(gameBoard,xPos,yPos,colour,0);
        total <<= 1;

        total += NW(gameBoard,xPos,yPos,colour,0);
        total <<= 1;*/
    }

    return total;
}

short int N(boardData *gameBoard, char xPos, int yPos, char colour, int n) {
    char **arr = gameBoard->board;
    short int myBool = 0;
    int x,y;

    x = xPos - 'a';
    y = yPos - 1;

    /*
     * Keep stepping up until 1 of these cases is reached
     * If I reach the edge of the board, then everything before hasn't been a vaild move therefore it's not a valid move flag it as such and break;
     * If I reach an empty space same logic as edge of board and break;
     * If I reach the same colour then there are 2 cases,
     *      either  this is the first piece I checked In which case the move is invalid, the default case so don't change anything and break;
     *      or      this isn't the first piece I checked, because every other case would've broke the loop that means that there were at least 1 piece of a different colour, therefore the move is valid and has been flagged as such so don't change the value and break;
     * If I reach a different colour piece it means that this move could possible be vaild so flag it as such
     *
     * If I reach the "edge" / "go out of bounds" then bool = 0; break;
     * If I reach an empty space bool = 0; break;
     * If I reach same colour, break;
     * If I reach a different colour, bool = 1; keep going
     */


    while (1){
        x = x;
        y = y - 1;

        if (y < 0){
            myBool = 0;
            break;
        }else if (arr[y][x] == '*'){
            myBool = 0;
            break;
        }else if (arr[y][x] == colour){
            break;
        }else{
            myBool = 1;
        }
    }

    if(n && myBool){
        x = xPos - 'a';
        y = yPos - 1;

        while (1){
            x = x;
            y = y - 1;

            if (y < 0){
                break;
            }else if (arr[y][x] == '*' || arr[y][x] == colour){
                break;
            }else{
                changeCell(gameBoard->board, xPos, 1 + y, colour);
            }
        }
    }

    return myBool;
}


