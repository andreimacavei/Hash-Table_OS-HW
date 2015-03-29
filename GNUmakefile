CC = gcc
CFLAGS = -Wall
EXEC = tema1

build: $(EXEC)

$(EXEC): main.o hash.o list.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c utils.h
	$(CC) $(CFLAGS) -c main.c

hash.o: hash.c hash.h utils.h
list.o: list.c list.h utils.h

clean:
	rm *.o $(EXEC)
