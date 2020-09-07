CC = gcc
CFLAGS = -Wall -static -pthread -g -O0

OBJECTS = tests.o net_test.o
EXEC = main

.PHONY: all clean run

all: $(OBJECTS)
	$(CC) -o $(EXEC) main.c $(OBJECTS) $(CFLAGS)

$(OBJECTS): %.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	@rm *.o

run:
	@./$(EXEC)
