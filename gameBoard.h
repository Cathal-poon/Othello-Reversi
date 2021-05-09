//
// Created by Cathal on 16/04/2021.
//
#include "players.h"

typedef struct {
    char **board;
    player player1;
    player player2;
} boardData;

#define BOARDSIZE 8

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
