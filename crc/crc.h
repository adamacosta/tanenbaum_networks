#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <unistd.h>

/* change for different crc bit-length */
typedef union {
	struct {
		char byte1;
		char byte2;
	} bytes;
	uint16_t c;
} crc;

#define GEN     0xA001	/* generator polynomial */
#define TRUE    1
#define FALSE   0

void init_crc_table();
crc update_crc(crc cur_crc, char c);