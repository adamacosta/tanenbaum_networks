CC     = gcc
CFLAGS = -Wall -std=c99
CLIBS = -lm

#### Build for test ####

all: generator verifier

generator: generator.c
	$(CC) -o generator  $(CFLAGS) generator.c $(CLIBS)

verifier: verifier.c
	$(CC) -o verifier $(CFLAGS) verifier.c

#### Cleanup ####

clean:
	rm -f generator verifier