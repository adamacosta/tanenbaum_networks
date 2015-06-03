/******************************************************************************
 * 
 * generator
 * ---------
 * Depends on crc.h
 *  
 * Receives byte stream from command-line argument and outputs the same byte
 * stream with CRC appended to stdout.  
 *
 *****************************************************************************/

#include "crc.h"

int main(int argc, char **argv) {

	if (argc != 2) {
		fprintf(stderr, "usage: generator [message]\n");
		exit(1);
	}

	crc c;
	int i;

	c.c = 0;
	for (i = 0; i < strlen(argv[1]); i++)
		c = update_crc(c, argv[1][i]);

	printf("%s%c%c", argv[1], c.bytes.byte1, c.bytes.byte2);

	return 0;
}