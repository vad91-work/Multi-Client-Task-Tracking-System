

CC = gcc
OPTIONS = -Wall -Wextra -Iinclude -g
SRC = src/server.c
OBJ = $(patsubst src/%.c, bin/%.o, $(SRC))
EXEC = bin/server

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OPTIONS) -o $@ $^
bin/%.o: src/%.c | bin
	$(CC) $(OPTIONS) -c $< -o $@
bin:
	mkdir -p bin
clean:
	rm -f $(OBJ) $(EXEC)

