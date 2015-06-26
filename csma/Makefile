CC = gcc
CFLAGS = -g -Wall
LIBS = -lpthread

SRC = csmacd.c
OBJ = $(patsubst %.c,%.o,$(SRC))

# pattern rule for object files
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

all: csmacd.o
	$(CC) -o csma csmacd.o $(LIBS)
	$(RM) -f *.o

clean:
	$(RM) -f *.o csma