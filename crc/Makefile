CC     = gcc
CFLAGS = -g -Wall -std=c99
LIBS  = -lm

#### Build for test ####

all: generator verifier

generator: generator.c
	$(CC) -o generator  $(CFLAGS) generator.c $(LIBS)

verifier: verifier.c
	$(CC) -o verifier $(CFLAGS) verifier.c $(LIBS)

#### Cleanup ####

clean:
	rm -f generator verifier