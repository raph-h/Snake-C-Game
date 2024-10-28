#include "main.h"

int main(int argc, char* argv[])
{
    int status = 0;
    if (argc != 2)
    {
        /* Give an error if arguments are incorrect */
        printf("usage %s <map_file>\n", argv[0]);
        status = 1;
    } else
    {
        initRandom(); /* Initialise the random */
        status = initGame(argv[1]); /* Initialise the game */
    }
    return status;
}