//
// Created by Cathal on 16/04/2021.
//

// used to create and manage and 8 * 8 square game board. Can do n * n by modifying "BOARDSIZE"

#include "players.h"

#define BOARDSIZE 8 // size of the n x n game board

// Structure to store information about the game.
typedef struct {
    char **board;
    player player1;
    player player2;
} boardData;

#ifndef ASSIGNMENT_2_GAMEBOARD_H
#define ASSIGNMENT_2_GAMEBOARD_H

void printBoard(boardData * gameBoard);
/*
 * Print a given game board with row and column headers
 */

char ** initialiseBoard();
/*
 * Generate and populate a game board
 */

void changeCell(char **arr, char x, int y, char c);
/*
 * Set a certain cell to a specific colour
 */

#endif //ASSIGNMENT_2_GAMEBOARD_H
