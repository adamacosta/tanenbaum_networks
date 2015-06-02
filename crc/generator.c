#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

#define GEN 0xD8
#define WIDTH (8 * sizeof(uint8_t))
#define TOPBIT (1 << (WIDTH - 1))
#define MAX_LEN 2048

typedef uint8_t crc;

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

int main(int argc, char **argv) {

	if (argc != 2) {
		fprintf(stderr, "usage: generator [message]\n");
		exit(1);
	}

	uint8_t msg[MAX_LEN];
	char out_msg[MAX_LEN];
	char pad[9];
	crc check;
	int i;
	size_t n_bytes;

	/* convert message to array of single-byte ints */
	n_bytes = strlen(argv[1]);
	for (i = 0; i < n_bytes; i++) {
		msg[i] = argv[1][i] - '0';
		out_msg[i] = argv[1][i];
	}
	out_msg[n_bytes] = '\0';
	check = get_crc(msg, n_bytes);
	binary_repr(check, pad);
	printf("%s", strcat(out_msg, pad));

	return 0;
}