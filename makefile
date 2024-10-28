CC = gcc
CFLAGS = -Wall -pedantic -ansi -Werror -g
OBJ = main.o game.o fileio.o map.o terminal.o random.o linkedlist.o
EXEC = treasure

ifdef DARK
CFLAGS += -D DARK
DARK: clean $(EXEC)
endif

ifdef COLOUR
CFLAGS += -D COLOUR
COLOUR: clean $(EXEC)
endif

ifdef DEBUG
CFLAGS += -D DEBUG
COLOUR: clean $(EXEC)
endif

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o: main.c main.h game.h random.h
	$(CC) $(CFLAGS) main.c -c

game.o: game.c game.h fileio.h map.h linkedlist.h
	$(CC) $(CFLAGS) game.c -c

fileio.o: fileio.c fileio.h map.h terminal.h
	$(CC) $(CFLAGS) fileio.c -c

map.o: map.c map.h random.h colour.h
	$(CC) $(CFLAGS) map.c -c

terminal.o: terminal.c terminal.h
	$(CC) $(CFLAGS) terminal.c -c

random.o: random.c random.h
	$(CC) $(CFLAGS) random.c -c

linkedlist.o: linkedlist.c linkedlist.h
	$(CC) $(CFLAGS) linkedlist.c -c

clean:
	rm $(OBJ) $(EXEC)