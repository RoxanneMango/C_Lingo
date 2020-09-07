CC = gcc
CFLAGS = -Wall -static -pthread -g -O0

OBJECTS = number_system_conversion.o error_handling.o file_io.o page_requests.o param.o lingo.o server.o high_scores.o
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
