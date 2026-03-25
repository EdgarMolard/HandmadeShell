CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -Iinclude

SRC = $(wildcard src/*.c) $(wildcard src/builtins/*.c)
OBJ = $(SRC:.c=.o)
TARGET = handmade_shell

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJ) $(TARGET)

re: clean all

.PHONY: all clean re
