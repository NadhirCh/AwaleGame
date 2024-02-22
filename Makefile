CC = gcc
CFLAGS = -I"./src/include/sdl2"
LDFLAGS = -L"./src/lib" -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -mwindows

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
EXEC = game.exe

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

run:
	./$(EXEC)

clean:
	del $(OBJ) $(EXEC)
