#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>

#include "random.h"
#include "colour.h"

/* Directions */
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

/* Objects */
#define AIR 0
#define WALL 1
#define LANTERN 2
#define PLAYER 3
#define SNAKE 4
#define TREASURE 5


#define FALSE 0
#define TRUE !FALSE


/* Struct containing data for the whole map */
typedef struct Map {
    int mapSizeX;
    int mapSizeY;
    int lantern;
    int** mapData;
} Map;

/* This function will initialise a map struct with size x and y */
Map* createMap(int x, int y);
/* This function will return a copy of a map */
Map* copyMap(Map* oldMap);
/* This function will free the memory for the map */
void freeMap(Map* map);
/* This function will free the memory for the map */
void freeMapAsVoid(void* map);

/* This function will display the map */
void printMap(Map* map, int playerX, int playerY);

/* This function will print the object at the position x and y */
void printObject(Map* map, int x, int y, int playerX, int playerY);

/* This function will set the x and y values to the position of the object found */
/* Ensure that there is only one of that type of object */
void getObjectPosition(Map* map, int object, int* x, int* y);

/* This function will test if an object in a direction */
/* It will return 0 if it can move to that location, else it will return whatever object is being moved on */
int canMoveObject(Map* map, int x, int y, int direction);

/* This function will move an object in a direction */
/* It will return 0 if it moves onto an empty square, or it will return the value of an object if it moves onto one */
int moveObject(Map* map, int x, int y, int direction);

/* This function will move an object to a specified location anywhere*/
/* It will set the original square to air */
/* It will return the object it moved onto */
int moveObjectToLocation(Map* map, int fromX, int fromY, int toX, int toY);

/* This function will move the snake */
/* Returns true if the snake has eaten the player */
int moveSnake(Map* map);

/* This function will move the snake randomly, having its current position */
void snakeRandomMove(Map* map, int x, int y);

#endif