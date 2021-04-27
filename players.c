//
// Created by Cathal on 23/04/2021.
//

#include "players.h"
#include <stdlib.h>
#include <stdio.h>

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
        printf("Please enter your player name:");
        fflush(stdin);
        scanf("%s",name);
        return name;
    }
}
