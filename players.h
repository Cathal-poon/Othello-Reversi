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
/*
 * Print out the players in the form
 * Score: [Player1]([Colour]) [Score]:[Score] [Player2]([Colour])
 */

void initPlayers(player * player1, player * player2);
/*
 * Initialise the two players,
 * read in names and assign colours
 */



#endif //ASSIGNMENT_2_PLAYERS_H
