#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef uint8_t crc;

#define GEN 0xD8 /* generator polynomial */
#define WIDTH (8 * sizeof(crc)) /* number of bits in CRC */
#define TOPBIT (1 << (WIDTH - 1))
#define MAX_LEN 2048 /* maximum message length, including CRC */

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

int main(int argc, char **argv) {

	if (argc != 2) {
		fprintf(stderr, "usage: verifier [message]\n");
		exit(1);
	}

	uint8_t *msg;
	crc check;
	int i;
	size_t n_bytes;

	/* convert message to array of single-byte ints */
	n_bytes = strlen(argv[1]);
	msg = malloc(n_bytes);
	for (i = 0; i < n_bytes; i++) {
		msg[i] = argv[1][i] - '0';
	}

	check = get_crc(msg, n_bytes); /* should be zero */
	free(msg);
	if (check)
		printf("error: crc not correct\n");
	else
		printf("success: crc correct\n");

	return 0;
}