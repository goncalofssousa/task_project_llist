CC = gcc
CFLAGS = -Wall -Iinclude
SRC = src/main.c src/tasks.c src/console.c
OBJ = $(SRC:.c=.o)
EXEC = build/task_manager

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

clean:
	rm -f src/*.o $(EXEC)
