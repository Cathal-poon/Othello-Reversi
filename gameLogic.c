//
// Created by Cathal on 15/05/2021.
//

#include "gameLogic.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


short int directionCheck(boardData * gameBoard, char x, int y, char colour, int direction);
// checks a given direction indicated by "direction"
short int doDirection(boardData * gameBoard, char x, int y, char colour, int n);
// does the move indicated by direction
int inLimits(char x, int y);
/*
 * Check if a location is inside the game board. return 1 if yes and 0 if no
 */
void doMove(boardData * gameBoard, char x, int y, char colour, unsigned short int encodedMoves);
/*
 * Do all the moves in encoded moves
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


int playerTurn(boardData *gameBoard, player currentPlayer) {
    char myX;
    int myY;
    int repeat = 1, moveChoices;
    unsigned short valid;

    printPlayers(&(gameBoard->player1),&(gameBoard->player2));
    moveChoices = updateBoard(*gameBoard, currentPlayer);
    printf("%s's (%c) turn\n", currentPlayer.name, currentPlayer.colour);

    if(moveChoices == 0){ // there are no vaild moves
        printf("No valid Moves. Passed\n");
        return 1; //pass
    }

    do {
        //fflush(stdin);
        printf("Please enter a valid move location on the board, letter then number; or enter 'p' for pass:\n");

        do {
            myX = (char) getchar(); // read in the letter
        } while (myX == '\n' || myX == ' '); // keep reading until it's not a common whitespace character
        // lets be do a move dump into the console

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
                // do the move
                changeCell(gameBoard->board, myX, myY, currentPlayer.colour);
                doMove(gameBoard, myX, myY, currentPlayer.colour, valid);
                repeat = 0; // update score should return 0 if there are empty spaces left

            }
        }

    } while (repeat);

    repeat += updateScore(gameBoard);
    return repeat;
}

int updateScore(boardData *gameBoard) {
    int black = 0, white = 0, total = 0; // counters to keep track of the number of pieces of their respective colour on the board
    char buffer;
    char ** arr;

    arr = gameBoard->board;

    for (int i = 0; i < BOARDSIZE; ++i) {
        for (int j = 0; j < BOARDSIZE; ++j) {
            buffer = arr[i][j];
            if (buffer == 'b'){
                black += 1;
                total += 0;
            } else if(buffer == 'w'){
                white += 1;
                total += 0;
            }
        }
    }


    if (gameBoard->player1.colour == 'b'){
        gameBoard->player1.score = black;
        gameBoard->player2.score = white;
    } else{
        gameBoard->player2.score = black;
        gameBoard->player1.score = white;
    }

    if (total == BOARDSIZE * BOARDSIZE){ // the board is full
        return 10;
    } else if(black == 0 || white == 0){
        return 10;
    } else{
        return 0;
    }
}

int updateBoard(boardData gameBoard, player currentPlayer) {
    char **arr;
    char xPos;
    int yPos;
    int total = 0;
    int valid;

    boardData tempBoard;

    arr = initialiseBoard();

    for (int i = 0; i < BOARDSIZE; ++i) {
        for (int j = 0; j < BOARDSIZE; ++j) {
            xPos = 'a' + j;
            yPos = 1 + i;

            arr[i][j] = gameBoard.board[i][j]; // copy over the current board's state
            valid = moveCheck(&gameBoard, xPos, yPos, currentPlayer.colour);
            if (valid){
                changeCell(arr,xPos,yPos,'*');
                total +=1;
            }
        }
    }

    tempBoard.board = arr;
    printBoard(tempBoard);
    free(arr);

    return total;
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
    if (gameBoard->board[y][x] == '\0'){
        // check all directions to see if there is a valid move
        total += directionCheck(gameBoard,xPos,yPos,colour,7); // add the return value to the total (should be 0 or 1)

        total <<= 1;
        total += directionCheck(gameBoard,xPos,yPos,colour,6);

        total <<= 1;
        total += directionCheck(gameBoard,xPos,yPos,colour,5);

        total <<= 1;
        total += directionCheck(gameBoard,xPos,yPos,colour,4);

        total <<= 1;
        total += directionCheck(gameBoard,xPos,yPos,colour,3);

        total <<= 1;
        total += directionCheck(gameBoard,xPos,yPos,colour,2);

        total <<= 1;
        total += directionCheck(gameBoard,xPos,yPos,colour,1);

        total <<= 1;
        total += directionCheck(gameBoard,xPos,yPos,colour,0);

    }

    return total;
}

short int directionCheck(boardData *gameBoard, char xPos, int yPos, char colour, int direction) {
    /*
     * Total encodes all possible moves and store them bitwise
     * N    - 7
     * NE   - 6
     * E    - 5
     * SE   - 4
     * S    - 3
     * SW   - 2
     * W    - 1
     * NW   - 0
     * 1 indicating it's a valid move
     * 0 indicating invalid
     * if all directions are valid then it will return 255
     * if only N is valid then it will return 128
     * if S and W are valid it will return 6
     */
    char **arr = gameBoard->board;
    short int myBool = 0;
    int x,y;

    x = xPos - 'a';
    y = yPos - 1;

    /*
     * Keep stepping up until 1 of these cases is reached
     * If I reach the edge of the board, then everything before hasn't been a valid move therefore it's not a valid move flag it as such and break;
     * If I reach an empty space same logic as edge of board and break;
     * If I reach the same colour then there are 2 cases,
     *      either  this is the first piece I checked In which case the move is invalid, the default case so don't change anything and break;
     *      or      this isn't the first piece I checked, because every other case would've broke the loop that means that there were at least 1 piece of a different colour, therefore the move is valid and has been flagged as such so don't change the value and break;
     * If I reach a different colour piece it means that this move could possible be valid so flag it as such
     *
     * If I reach the "edge" / "go out of bounds" then bool = 0; break;
     * If I reach an empty space bool = 0; break;
     * If I reach same colour, break;
     * If I reach a different colour, bool = 1; keep going
     */


    while (1){

        switch (direction) {
            case 0:
                // NW
                x = x - 1;
                y = y - 1;
                break;
            case 1:
                // W
                x = x - 1;
                y = y;
                break;
            case 2:
                // SW
                x = x - 1;
                y = y + 1;
                break;
            case 3:
                // S
                x = x;
                y = y + 1;
                break;
            case 4:
                // SE
                x = x + 1;
                y = y + 1;
                break;
            case 5:
                // E
                x = x + 1;
                y = y;
                break;
            case 6:
                // NE
                x = x + 1;
                y = y - 1;
                break;
            case 7:
                // N
                x = x;
                y = y - 1;
                break;
            default:
                x = x;
                y = y - 1;
        }

        if (y < 0 || y >= BOARDSIZE || x < 0 || x >= BOARDSIZE){
            myBool = 0;
            break;
        }else if (arr[y][x] == '\0' || arr[y][x] == '*'){ // check if it's an empty space
            myBool = 0;
            break;
        }else if (arr[y][x] == colour){
            break;
        }else{
            myBool = 1;
        }
    }
    return myBool;
}

short int doDirection(boardData *gameBoard, char xPos, int yPos, char colour, int direction) {
    char ** arr = gameBoard->board;
    int x,y;


    x = xPos - 'a';
    y = yPos - 1;

    while (1){
        switch (direction) {
            case 0:
                x = x - 1;
                y = y - 1;
                break;
            case 1:
                x = x - 1;
                y = y;
                break;
            case 2:
                x = x - 1;
                y = y + 1;
                break;
            case 3:
                x = x;
                y = y + 1;
                break;
            case 4:
                x = x + 1;
                y = y + 1;
                break;
            case 5:
                x = x + 1;
                y = y;
                break;
            case 6:
                x = x + 1;
                y = y - 1;
                break;
            case 7:
                x = x;
                y = y - 1;
                break;
            default:
                x = x;
                y = y - 1;
        }

        if (y < 0 || y >= BOARDSIZE || x < 0 || x >= BOARDSIZE){
            break;
        }else if (arr[y][x] == '\0' || arr[y][x] == colour){ // check if it's an empty space or has the same colour
            break;
        }else{
            changeCell(gameBoard->board, x + 'a', 1 + y, colour);
        }
    }



    return 0;
}

void doMove(boardData * gameBoard, char xPos, int yPos, char colour, unsigned short int encodedMoves) {
    // bitwise and checks a specific location in the encoded moves and returns 0 if there's nothing or > 1 if there is something
    if(encodedMoves & 128){
        doDirection(gameBoard, xPos, yPos, colour, 7);
    }

    if(encodedMoves & 64){
        doDirection(gameBoard, xPos, yPos, colour, 6);
    }

    if(encodedMoves & 32){
        doDirection(gameBoard, xPos, yPos, colour, 5);
    }

    if(encodedMoves & 16){
        doDirection(gameBoard, xPos, yPos, colour, 4);
    }

    if(encodedMoves & 8){
        doDirection(gameBoard, xPos, yPos, colour, 3);
    }

    if(encodedMoves & 4){
        doDirection(gameBoard, xPos, yPos, colour, 2);
    }

    if(encodedMoves & 2){
        doDirection(gameBoard, xPos, yPos, colour, 1);
    }

    if(encodedMoves & 1){
        doDirection(gameBoard, xPos, yPos, colour, 0);
    }

}


// 小der