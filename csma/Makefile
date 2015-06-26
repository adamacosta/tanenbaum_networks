CC = gcc
CFLAGS = -g -Wall
LIBS = -lpthread

SRC = main.c master.c station.c csma.c
OBJ = $(patsubst %.c,%.o,$(SRC))

# pattern rule for object files
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

all: $(OBJ)
	$(CC) -o csma $(OBJ) $(LIBS)
	$(RM) -f *.o

clean:
	$(RM) -f *.o csma