

CC = gcc
OPTIONS = -Wall -Wextra -Iinclude -g
SRC = src/main.c
OBJ = $(patsubst src/%.c, bin/%.o, $(SRC))
EXEC = bin/server

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OPTIONS) -o $@ $^
bin/%.o: src/%.c
	$(CC) $(OPTIONS) -c $< -o $@
clean:
	rm -f $(OBJ) $(EXEC)

