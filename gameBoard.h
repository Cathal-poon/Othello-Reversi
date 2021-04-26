//
// Created by Cathal on 16/04/2021.
//
#define BOARDSIZE 8

#ifndef ASSIGNMENT_2_GAMEBOARD_H
#define ASSIGNMENT_2_GAMEBOARD_H

void printBoard(char arr[BOARDSIZE][BOARDSIZE]);
/*
 * Print a given game board with row and column headers
 */

void initialiseBoard(char arr[BOARDSIZE][BOARDSIZE]);
/*
 * Generate and populate a game board
 */

void changeCell(char arr[BOARDSIZE][BOARDSIZE], char x, int y, char c);
/*
 * Set a certain cell to a specific colour
 */

#endif //ASSIGNMENT_2_GAMEBOARD_H
