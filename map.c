#include "map.h"

Map* createMap(int x, int y)
{
    int i;
    Map* map = (Map*)malloc(sizeof(Map)); /* Allocate space for a single map */
    map->mapSizeX = x;
    map->mapSizeY = y;
    map->lantern = FALSE;
    map->mapData = (int**)malloc(x * sizeof(int*)); /* Allocate a 2D array space */
    for (i = 0; i < x; i++)
    {
        map->mapData[i] = (int*)malloc(y * sizeof(int));
    }
    return map;
}

Map* copyMap(Map* oldMap)
{
    int i, j;
    /* Create a map with same parameters as the current one */
    Map* newMap = createMap(oldMap->mapSizeX, oldMap->mapSizeY);
    /* Set the other info such as lantern & copy over map data */
    newMap->lantern = oldMap->lantern;
    for (i = 0; i < oldMap->mapSizeX; i++)
    {
        for (j = 0; j < oldMap->mapSizeY; j++)
        {
            newMap->mapData[i][j] = oldMap->mapData[i][j];
        }
    }
    return newMap;
}

void freeMap(Map* map)
{
    int i;
    for (i = 0; i < map->mapSizeX; i++)
    {
        free(map->mapData[i]); /* Free the map data array */
    }
    free(map->mapData); /* Free the map data */
    free(map); /* Free the map */
}

void freeMapAsVoid(void* map)
{
    freeMap((Map*) map); /* Free the map, but typecast to a map from a void ptr */
}

void printMap(Map* map, int playerX, int playerY)
{
    int i, j;

    system("tput cup 0 0"); /* Move the cursor to the very top to display */
    #ifdef COLOUR
    printf(BLK);
    #endif
    for (j = 0; j < map->mapSizeY + 2; j++)
    {
        printf("*"); /* Print the top border */
    }
    printf("\n");
    /* Print the contents */
    for (i = 0; i < map->mapSizeX; i++)
    {
        printf("*");
        #ifdef COLOUR
        printf(RESET);
        #endif
        for (j = 0; j < map->mapSizeY; j++)
        {
            printObject(map, i, j, playerX, playerY);
        }
        #ifdef COLOUR
        printf(BLK);
        #endif
        printf("*\n");
    }
    for (j = 0; j < map->mapSizeY + 2; j++)
    {
        printf("*"); /* Print the bottom border */
    }
    #ifdef COLOUR
    printf(RESET);
    #endif
    printf("\n"); /* Print instructions */
    printf("Press w to move up\n");
    printf("Press s to move down\n");
    printf("Press a to move left\n");
    printf("Press d to move right\n");
    printf("Press u to undo\n");
    #ifdef DEBUG
    for (i = 0; i < 255; i++) {
        printf("\x1b[38;5;%dmX", i);
    }
    #endif
}

void printObject(Map* map, int x, int y, int playerX, int playerY)
{
    char object;
    #ifdef DARK
    int distance;
    #endif
    #ifdef COLOUR
    int col = FALSE;
    #endif

    if (map->mapData[x][y] == AIR)
    {
        #ifdef DARK
        object = '.'; /* If dark, print it as .*/
        #else
        object = ' ';
        #endif
    } else if (map->mapData[x][y] == WALL)
    {
        #ifdef COLOUR
        printf(COL"232m");
        col = TRUE;
        #endif
        object = 'O';
    } else if (map->mapData[x][y] == LANTERN)
    {
        #ifdef COLOUR
        printf(COL"208m");
        col = TRUE;
        #endif
        object = '@';
    } else if (map->mapData[x][y] == PLAYER)
    {
        #ifdef COLOUR
        printf(BLU);
        col = TRUE;
        #endif
        object = 'P';
    } else if (map->mapData[x][y] == SNAKE)
    {
        #ifdef COLOUR
        printf(RED);
        col = TRUE;
        #endif
        object = '~';
    } else if (map->mapData[x][y] == TREASURE)
    {
        #ifdef COLOUR
        printf(YEL);
        col = TRUE;
        #endif
        object = '$';
    }
    #ifdef DARK
    if (map->lantern)
    {
        distance = 6;
    } else
    {
        distance = 3;
    }
    if (abs(playerX - x) + abs(playerY - y) > distance)
    {
        object = ' ';  /* If dark, and distance is further than player, print whitespace */
    }
    #endif
    printf("%c", object);
    #ifdef COLOUR
    if (col) {
        printf(RESET);
    }
    #endif
}

void getObjectPosition(Map* map, int object, int* x, int* y)
{
    int i, j;
    for (i = 0; i < map->mapSizeX; i++)
    {
        for (j = 0; j < map->mapSizeY; j++)
        {
            if (map->mapData[i][j] == object)
            {
                *x = i; /* Set position values to where the object is */
                *y = j;
            }
        }
    }
}

int canMoveObject(Map* map, int x, int y, int direction)
{
    int object = WALL; /* Assume it will touch a wall */
    if (direction == LEFT)
    {
        if (y > 0)
        {
            if (map->mapData[x][y - 1] != WALL)
            {
                object = map->mapData[x][y - 1];
            }
        }
    } else if (direction == RIGHT)
    {
        if (y < map->mapSizeY - 1)
        {
            if (map->mapData[x][y + 1] != WALL)
            {
                object = map->mapData[x][y + 1];
            }
        }
    } else if (direction == UP)
    {
        if (x > 0)
        {
            if (map->mapData[x - 1][y] != WALL)
            {
                object = map->mapData[x - 1][y];
            }
        }
    } else if (direction == DOWN)
    {
        if (x < map->mapSizeX - 1)
        {
            if (map->mapData[x + 1][y] != WALL)
            {
                object = map->mapData[x + 1][y];
            }
        }
    }
    return object; /* Return the object in the direction specified */
}

int moveObject(Map* map, int x, int y, int direction)
{
    int object = WALL;
    if (canMoveObject(map, x, y, direction) != WALL)
    {
        if (direction == LEFT)
        {
            object = moveObjectToLocation(map, x, y, x, y - 1);
        } else if (direction == RIGHT)
        {
            object = moveObjectToLocation(map, x, y, x, y + 1);
        } else if (direction == UP)
        {
            object = moveObjectToLocation(map, x, y, x - 1, y);
        } else if (direction == DOWN)
        {
            object = moveObjectToLocation(map, x, y, x + 1, y);
        }
    }
    return object;
}

int moveObjectToLocation(Map* map, int fromX, int fromY, int toX, int toY)
{
    int object = map->mapData[toX][toY]; /* Get the object at the new position */
    map->mapData[toX][toY] = map->mapData[fromX][fromY]; /* Move the object at the old position to the new one */
    map->mapData[fromX][fromY] = AIR; /* Set the object at the old position as AIR */
    return object; /* Return the object which was moved onto */
}

int moveSnake(Map* map)
{
    int x, y, eaten = FALSE;
    int playerX, playerY;
    getObjectPosition(map, SNAKE, &x, &y);
    getObjectPosition(map, PLAYER, &playerX, &playerY);
    /* If the snake is 1 tile away from the player*/
    if (abs(playerX - x) <= 1 && abs(playerY - y) <= 1)
    {
        map->mapData[playerX][playerY] = map->mapData[x][y];
        map->mapData[x][y] = AIR;
        eaten = TRUE;
    } else
    {
        snakeRandomMove(map, x, y); /* Move snake randomly */
    }
    return eaten;
}

void snakeRandomMove(Map* map, int x, int y)
{
    int direction, iterations = 0;
    int validMove = FALSE;
    while (!validMove && iterations < 5000) /* Will check for valid moves for 5000 times, if it has not achieved a valid move, will then stop */
    {
        direction = randomInt(1, 8); /* Get a random direction */
        /* If direction is along x or y direction direction */
        if (direction == UP || direction == DOWN || direction == LEFT || direction == RIGHT)
        {
            if (canMoveObject(map, x, y, direction) == AIR)
            {
                validMove = TRUE;
                moveObject(map, x, y, direction);
            }
        } else if (direction == RIGHT + UP || direction == RIGHT + DOWN) /* If direction is diagonally right*/
        {
            if (y < map->mapSizeY - 1) /* If it is not touching bounds */
            {
                if (canMoveObject(map, x, y + 1, direction - RIGHT) == AIR) /* If it can move diagonally */
                {
                    validMove = TRUE;
                    if (direction - RIGHT == UP) /* Diagonally right up */
                    {
                        moveObjectToLocation(map, x, y, x - 1, y + 1);
                    } else /* Diagonally right down */
                    {
                        moveObjectToLocation(map, x, y, x + 1, y + 1);
                    }
                }
            }
        } else if (direction == LEFT + 3 + UP || direction == LEFT + 3 + DOWN) /* If direction is diagonally left*/
        {
            if (y > 0) /* If it is not touching bounds */
            {
                if (canMoveObject(map, x, y - 1, direction - (LEFT + 3)) == AIR) /* If it can move diagonally */
                {
                    validMove = TRUE;
                    if (direction - (LEFT + 3) == UP) /* Diagonally left up */
                    {
                        moveObjectToLocation(map, x, y, x - 1, y - 1);
                    } else /* Diagonally left down */
                    {
                        moveObjectToLocation(map, x, y, x + 1, y - 1);
                    }
                }
            }
        }
        iterations++;
    }
    if (!validMove) /* If snake cannot find a move after checking 5000 times */
    {
        printf("Snake could not find valid move!\n");
    }
}