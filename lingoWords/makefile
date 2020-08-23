CC = gcc
CFLAGS = -Wall -static

OBJECTS = lingo_words.o
EXEC = main

.PHONY: all clean

all: $(OBJECTS)
	$(CC) -o $(EXEC) main.c $(OBJECTS) $(CFLAGS)
	@./$(EXEC)

$(OBJECTS): %.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
clean:
	@rm *.o
