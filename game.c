#include "game.h"

int initGame(char* mapFile)
{
    int status = 0;
    /* Initialise a linkedlist which contains a history of maps*/
    LinkedList* mapLinkedList = createLinkedList();
    Map* map = NULL; /* Current map */
    status = openMapFile(mapFile, &map); /* Open map from file */
    if (map != NULL && status == 0) /* If map file exists & map is created with no errors */
    {
        insertStart(mapLinkedList, map);
        status = gameLoop(mapLinkedList);
    } else { /* Map was not created */
        printf("Error: Could not create map");
    }
    /* Free data */
    freeLinkedList(mapLinkedList, &freeMapAsVoid);
    map = NULL;
    mapLinkedList = NULL;
    return status;
}

int gameLoop(LinkedList* mapLinkedList)
{
    int status = 0;
    int running = TRUE, win;
    int playerX, playerY;

    system("clear"); /* Clear the terminal to start with it empty */
    /* Get position of player */
    getObjectPosition(mapLinkedList->head->data, PLAYER, &playerX, &playerY);
    /* Print the map file before the player moves */
    printMap(mapLinkedList->head->data, playerX, playerY);
    while (running)
    {
        int object;
        char input;

        readChar(&input);
        if (input == 'u') /* Undo */
        {
            if (mapLinkedList->head->next != NULL)
            {
                freeMap((Map*) removeStart(mapLinkedList));
            }
        } else if (input == 'w' || input == 's' || input == 'a' || input == 'd') {
            insertStart(mapLinkedList, copyMap(mapLinkedList->head->data));
            if (input == 'w') /* Up */
            {
                object = moveObject(mapLinkedList->head->data, playerX, playerY, UP);
            } else if (input == 's') /* Down */
            {
                object = moveObject(mapLinkedList->head->data, playerX, playerY, DOWN);
            } else if (input == 'a') /* Left */
            {
                object = moveObject(mapLinkedList->head->data, playerX, playerY, LEFT);
            } else if (input == 'd') /* Right */
            {
                object = moveObject(mapLinkedList->head->data, playerX, playerY, RIGHT);
            }
            if (object == SNAKE) /* If player moves onto the snake */
            {
                running = FALSE; /* They still lose */
                win = FALSE;
                getObjectPosition(mapLinkedList->head->data, PLAYER, &playerX, &playerY);
                ((Map*) (mapLinkedList->head->data))->mapData[playerX][playerY] = SNAKE; /* Replace snake with player so it looks like snake ate the player */
            } else if (moveSnake(mapLinkedList->head->data)) /* If snake moves into the player */
            {
                running = FALSE;
                win = FALSE;
            }
            if (object == LANTERN)
            {
                ((Map*) mapLinkedList->head->data)->lantern = TRUE;
            } else if (object == TREASURE)
            {
                running = FALSE;
                win = TRUE;
            }
        }
        getObjectPosition(mapLinkedList->head->data, PLAYER, &playerX, &playerY);
        printMap(mapLinkedList->head->data, playerX, playerY);
    }
    if (win)
    {
        printf("Player win!\n");
    } else
    {
        printf("Player lose\n");
    }
    return status;
}