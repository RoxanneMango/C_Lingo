CC = gcc
CFLAGS = -Wall -static -O3 
EXEC = main

.PHONY: all clean run

all: $(OBJECTS)
	$(CC) -o $(EXEC) main.c $(CFLAGS)

clean:
	@rm $(EXEC)

run:
	@./$(EXEC)
