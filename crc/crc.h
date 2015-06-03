#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

typedef uint8_t crc;

#define GEN 0xD8 /* generator polynomial */
#define WIDTH (8 * sizeof(crc)) /* number of bits in CRC */
#define TOPBIT (1 << (WIDTH - 1))
#define MAX_LEN 2048 /* maximum message length, including CRC */

/* computes CRC over an array of single-byte ints */
crc get_crc(uint8_t const message[], int n_bytes) {
	crc remainder = 0;
	uint8_t bit;
	int byte;

	for (byte = 0; byte < n_bytes; byte++) {
		remainder ^= (message[byte] << (WIDTH - 8));
		for (bit = 8; bit > 0; bit--) {
			if (remainder & TOPBIT)
				remainder = (remainder << 1) ^ GEN;
			else
				remainder = (remainder << 1);
		}
	}

	return remainder;
}

/* returns 8-bit binary representation of a single-byte int */
void binary_repr(int n, char s[]) {
	int i;
	int bin_dig;
	int len = (int)ceil(log2(n));
	int pad;

	if (len < 8) {
		pad = 8 - len;
		for (i = 0; i < pad; i++)
			s[i] = '0';
	}

	for (i = 0; i < len; i++) {
		bin_dig = n >> (len - 1 - i);
		n -= bin_dig << (len -1 - i);
		if (bin_dig == 1)
			s[i + pad] = '1';
		else
			s[i + pad] = '0';
	}

	s[8] = '\0';
}