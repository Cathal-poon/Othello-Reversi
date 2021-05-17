//
// Created by Cathal on 15/05/2021.
//

#include "gameBoard.h"

#ifndef ASSIGNMENT_2_GAMELOGIC_H
#define ASSIGNMENT_2_GAMELOGIC_H

int playerTurn(boardData * gameBoard, player currentPlayer);
/*
 * Takes in a move from the player and checks if that move is a valid move.
 * Keeps asking until a valid move is entered or the player has passed
 * Returns 0 if a valid move was played and 1 if the player passed
 */

void updateScore(boardData * gameBoard);
/*
 * Updates the score of the current game
 */

#endif //ASSIGNMENT_2_GAMELOGIC_H
