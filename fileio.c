#include "fileio.h"

int openMapFile(char fileName[], Map** mapPtr)
{
    int status;
    FILE* fmap = fopen(fileName, "r");
    
    if (fmap == NULL)
    {
        perror("Could not open file");
        status = 1;
    } else
    {
        int x, y, numWall;
        if (fscanf(fmap, "%d %d", &x, &y) != EOF) /* Scan first line containing dimensions */
        {
            if (fscanf(fmap, "%d", &numWall) != EOF) /* Scan second line containing number of walls */
            {
                Map* map = createMap(x, y); /* If successful, create map and read map data */
                *mapPtr = map;
                status = readMapData(fmap, map);
                /*printMapDebug(map);*/
            /*if (ferror(fmap)) {
                perror("Error reading from file");
                status = 1;
            } else {
                
            }*/
            } else
            {
                status = 1; /* Fail if map cant be read */
            }
        } else
        {
            status = 1; /* Fail if map cant be read */
        }
        
        if (fclose(fmap))
        {
            perror("File close error");
            status = 1;
        }
    }

    return status;
}

int readMapData(FILE* fmap, Map* map)
{
    int i, j, status = 0;
    /* Loop through map size */
    for (i = 0; i < map->mapSizeX; i++)
    {
        for (j = 0; j < map->mapSizeY; j++)
        {
            /* Scan the digit and store into the 2D array */
            fscanf(fmap, "%d", &map->mapData[i][j]);
            if (ferror(fmap)) /* If there is an error, return 1 */
            {
                status = 1;
            }
        }
    }
    return status;
}

void readChar(char* c)
{
    disableBuffer(); /* Disable displaying the input */
    scanf(" %c", c); /* Get input from user */
    enableBuffer(); /* Enable displaying the input */
}