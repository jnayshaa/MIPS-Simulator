CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -Iinclude

SRC=src/main.c src/cpu.c src/execute.c src/parser.c src/cache.c
OUT=mips_sim

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)
