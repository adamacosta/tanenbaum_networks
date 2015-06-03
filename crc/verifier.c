#include "crc.h"

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