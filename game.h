#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>

#include "fileio.h"
#include "map.h"
#include "linkedlist.h"

#define FALSE 0
#define TRUE !FALSE

/* Starts the game, with a map filename */
int initGame(char* mapFile);

/* The game loop which is called until the game exits */
int gameLoop(LinkedList* mapLinkedList);

#endif