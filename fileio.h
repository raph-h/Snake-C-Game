#ifndef FILEIO_H
#define FILEIO_H

#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "terminal.h"

/* This function will open a file and obtain the map size, number of walls and then call readMapData() to obtain all the data */
int openMapFile(char fileName[], Map** map);

/* This function will read the data containing the positions of all the objects in the map file */
int readMapData(FILE* fmap, Map* map);

/* Functions used are obtained from COMP1000 assignment resources */
/* This function will read a character from the terminal instantly without pressing enter */
void readChar(char* c);

#endif