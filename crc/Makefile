CC     = gcc
CFLAGS = -g -Wall -std=c99
LIBS   = -lm
HDR    = crc.h
INC    = crc.c

#### Build for test ####

all: generator verifier

generator: generator.c $(INC) $(HDR)
	$(CC) -o generator  $(CFLAGS) generator.c $(INC) $(LIBS)

verifier: verifier.c $(INC) $(HDR)
	$(CC) -o verifier $(CFLAGS) verifier.c $(INC) $(LIBS)

alter: alter.c $(INC) $(HDR)
	$(CC) -o alter $(CFLAGS) alter.c $(INC) $(LIBS)

#### Cleanup ####

clean:
	rm -f generator verifier