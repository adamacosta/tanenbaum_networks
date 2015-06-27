/******************************************************************************
 * 
 * verifier
 * --------
 * Depends on crc.h
 * 
 * Receives input from stdin with CRC appended and verifies input not corrupted
 * 
 *****************************************************************************/

#include "crc.h"

int main(int argc, char **argv) {
	crc c;
	char s;

	c.c = 0;
	while (read(0, &s, 1) > 0)
		c = update_crc(c, s);

	if (c.c)
		printf("error: crc not correct\n");
	else
		printf("success: crc correct\n");

	return 0;
}