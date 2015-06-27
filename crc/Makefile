CC       = gcc
CFLAGS   = -g -Wall -std=c99
LIBS     = -lm
SRC_DIR  = src
TEST_DIR = tests
BIN_DIR  = bin
HDR      = $(SRC_DIR)/crc.h
INC      = $(SRC_DIR)/crc.c

#### Build for test ####

all: generator verifier alter

generator: $(SRC_DIR)/generator.c $(INC) $(HDR)
	$(CC) -o $(BIN_DIR)/generator  $(CFLAGS) $(SRC_DIR)/generator.c $(INC) $(LIBS)
	$(RM) -f *.o

verifier: $(SRC_DIR)/verifier.c $(INC) $(HDR)
	$(CC) -o $(BIN_DIR)/verifier $(CFLAGS) $(SRC_DIR)/verifier.c $(INC) $(LIBS)
	$(RM) -f *.o

alter: $(SRC_DIR)/alter.c $(INC) $(HDR)
	$(CC) -o $(BIN_DIR)/alter $(CFLAGS) $(SRC_DIR)/alter.c $(INC) $(LIBS)
	$(RM) -f *.o

#### Cleanup ####

clean:
	$(RM) -f $(BIN_DIR)/generator $(BIN_DIR)/verifier $(BIN_DIR)/alter