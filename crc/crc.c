#include "crc.h"

static crc crc_table[256];
static int crc_table_init = FALSE;

/* initialize crc16 table */
void init_crc_table() {
	int i, j;
	uint16_t init_crc, c;

	for (i = 0; i < 256; i++) {
		init_crc = 0;
		c = (uint16_t) i;

		for (j = 0; j < 8; j++) {
			if ((init_crc ^ c) & 0x0001)
				init_crc = (init_crc >> 1) ^ GEN;
			else
				init_crc = init_crc >> 1;
			c >>= 1;
		}
		crc_table[i].c = init_crc;
	}
	crc_table_init = TRUE;
}

/* update crc16 per byte */
crc update_crc(crc cur_crc, char c) {
	crc tmp, uc;

	uc.c = 0x00ff & (uint16_t)c;

	if (!crc_table_init)
		init_crc_table();

	tmp.c = cur_crc.c ^ uc.c;
	cur_crc.c = (cur_crc.c >> 8) ^ crc_table[tmp.c & 0xff].c;

	return cur_crc;
}