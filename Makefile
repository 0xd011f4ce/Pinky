CC=gcc
ECHO=echo -e

CFLAGS=-Wall -Werror -std=gnu99 -O0 -g
LIBS=

FILES=build/main.o
OUT=bin/pinky.out

all: $(FILES)
	@$(ECHO) "CC\t\t"$(FILES)
	@$(CC) $(CFLAGS) $(FILES) -o $(OUT) $(LIBS)

build/main.o: src/main.c
	@$(ECHO) "CC\t\t"$<
	@$(CC) $(CFLAGS) $< -c -o $@ $(LIBS)

clean:
	@$(ECHO) "Cleaning the project"
	@rm -f $(FILES) $(OUT)
	@$(ECHO) "Clean finished"
