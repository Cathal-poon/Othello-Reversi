//
// Created by Cathal on 23/04/2021.
//

#include "players.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_CHAR 10
/*
struct _player{
    char *name;
    char colour;
    int score;
};

*/

char *getName() {
    char *name = (char*) malloc(MAX_CHAR * sizeof(char));

    if (name == NULL){
        printf("Error allocating memory");
        return NULL;
    } else {
        fflush(stdin);
        scanf("%s",name);
        name[strcspn(name,"\n")] = '\0'; // remove the trailing newline character and replace it with a null character
        return name;
    }
}

void printPlayers(const player  * const player1, const player * const player2) {
    char *ptr1 = NULL, *ptr2 = NULL;
    char strWhite[] = "White";
    char strBlack[] = "Black";

    if (player1->colour == 'w'){
        ptr1 = strWhite;
        ptr2 = strBlack;
    } else{
        ptr1 = strBlack;
        ptr2 = strWhite;
    }

    printf("Score: %s (%s) %d:%d %s (%s)\n",
           player1->name,
           ptr1,
           player1->score,
           player2->score,
           player2->name,
           ptr2
           );
}

void initPlayers(player * const player1, player * const player2) {
    srand(time(NULL));

    if (rand()%2){
        player1->colour = 'b';
        player2->colour = 'w';
    } else {
        player1->colour = 'w';
        player2->colour = 'b';
    }

    player1->score = 2;
    player2->score = 2;

    printf("Please enter your player1's name:");
    player1->name = getName();

    printf("Please enter your player2's name:");
    player2->name = getName();
}
