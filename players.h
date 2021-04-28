//
// Created by Cathal on 23/04/2021.
//

#ifndef ASSIGNMENT_2_PLAYERS_H
#define ASSIGNMENT_2_PLAYERS_H

typedef struct {
    char *name;
    char colour;
    int score;
} player;



void printPlayers(const player  * player1, const player * player2);

#endif //ASSIGNMENT_2_PLAYERS_H
