CC = gcc
CFLAGS = -Wall -static -pthread

OBJECTS = number_system_conversion.o error_handling.o file_io.o page_requests.o param.o lingo.o server.o
EXEC = main

.PHONY: all clean

all: $(OBJECTS)
	$(CC) -o $(EXEC) main.c $(OBJECTS) $(CFLAGS)
	@./$(EXEC)

$(OBJECTS): %.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
clean:
	@rm *.o
