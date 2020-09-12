CC = gcc
CFLAGS = -Wall -static -g -O0

OBJECTS = 
EXEC = main

.PHONY: all clean run

all: $(OBJECTS)
	$(CC) -o $(EXEC) main.c $(OBJECTS) $(CFLAGS)

$(OBJECTS): %.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	@rm *.o
	@rm $(EXEC)

run:
	@./$(EXEC)
