

CC = gcc
OPTIONS = -Wall -Wextra -Iinclude -g -lmysqlclient
SRC = src/server.c src/database.c
OBJ = $(patsubst src/%.c, bin/%.o, $(SRC))
EXEC = bin/server

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OPTIONS) -o $@ $^
bin/%.o: src/%.c
	$(CC) $(OPTIONS) -c $< -o $@
clean:
	rm -f $(OBJ) $(EXEC)

