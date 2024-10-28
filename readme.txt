# SNAKE GAME
Game where you must move a player `P` in a map to reach the treasure marked '$' and touch it without getting eaten by the snake
In dark mode, the map is partially visible, with the lantern marked `@` improving visibility

This game is created for the UCP assignment and has been adapted to include more simple features
- Colour, objects are coloured instead of being just white
- Basic error checking on map files

## Makefile Compilation
`make`
Compile with dark mode
`make DARK=1`
Compile with colour
`make COLOUR=1`
Compile with dark mode and colour
`make DARK=1 COLOUR=1`

## Improvements
- Currently the linkedlist stores all data on the map, this allows more feature to be added in the future, however it increases memory usage

## Map files
- There are some example map files in ./maps
- Each map file contains the size of the map as the first line, then number of walls (unused from assignment) and then map data
- 0 for nothing, 1 for wall, 2 for lantern, 3 for player, 4 for snake, 5 for treasure