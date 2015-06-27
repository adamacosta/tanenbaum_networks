CC = gcc
CFLAGS = -g -Wall
LIBS = -lpthread

SRC_DIR = src
BUILD_DIR = bin

SRC = $(SRC_DIR)/main.c $(SRC_DIR)/master.c $(SRC_DIR)/station.c \
      $(SRC_DIR)/csma.c
OBJ = $(patsubst %.c,%.o,$(SRC))

# pattern rule for object files
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

all: $(OBJ)
	$(CC) -o $(BUILD_DIR)/csma $(OBJ) $(LIBS)
	$(RM) -f $(SRC_DIR)/*.o

clean:
	$(RM) -f $(SRC_DIR)/*.o $(BUILD_DIR)/csma