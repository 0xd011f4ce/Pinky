CC=gcc
ECHO=echo -e

CFLAGS=-Wall -Werror -std=gnu99 -O0 -g -Iinclude
LIBS=

FILES=build/main.o build/utils/vector.o build/utils/buffer.o

OUT=bin/pinky.out

all: $(FILES)
	@$(ECHO) "CC\t\t"$(FILES)
	@$(CC) $(CFLAGS) $(FILES) -o $(OUT) $(LIBS)

build/main.o: src/main.c
	@$(ECHO) "CC\t\t"$<
	@$(CC) $(CFLAGS) $< -c -o $@ $(LIBS)

build/utils/vector.o: src/utils/vector.c
	@$(ECHO) "CC\t\t"$<
	@$(CC) $(CFLAGS) $< -c -o $@ $(LIBS)

build/utils/buffer.o: src/utils/buffer.c
	@$(ECHO) "CC\t\t"$<
	@$(CC) $(CFLAGS) $< -c -o $@ $(LIBS)

clean:
	@$(ECHO) "Cleaning the project"
	@rm -f $(FILES) $(OUT)
	@$(ECHO) "Clean finished"
