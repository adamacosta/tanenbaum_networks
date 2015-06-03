#include "crc.h"

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