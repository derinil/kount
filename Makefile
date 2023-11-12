UNAME_S = $(shell uname -s)

CC = clang
CFLAGS = -std=c99 -Wall -Wextra -Wpedantic -Wstrict-aliasing
CFLAGS += -Ofast -ffast-math
LDFLAGS =

SRC  = $(wildcard src/**/*.c) $(wildcard src/*.c) $(wildcard src/**/**/*.c) $(wildcard src/**/**/**/*.c)
OBJ  = $(SRC:.c=.o)
BIN = bin

.PHONY: all clean

all: dirs build

dirs:
	mkdir -p ./$(BIN)

build: $(OBJ)
	$(CC) -o $(BIN)/kount $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(BIN) $(OBJ)
