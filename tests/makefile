CC = gcc
CFLAGS = -Wall -static -O3

OBJECTS = tests.o net_test.o file_test.o mem_test.o
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
