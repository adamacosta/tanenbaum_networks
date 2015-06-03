#include "crc.h"

int main(int argc, char **argv) {
	char c;
	int i;

	srand(1234);

	while (read(0, &c, 1) > 0) {
		for (i = 0; i < 8; i++)
			if (rand() < RAND_MAX / 100) /* flips 1% of the bits */
				c ^= (unsigned char)0x80 >> i;
		write(1, &c, 1);
	}

	return 0;
}