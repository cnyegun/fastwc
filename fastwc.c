#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>

static const uint8_t iswhitespace[256] = {
	[' ']  = 1,
	['\t'] = 1,
	['\n'] = 1,
	['\r'] = 1,
	['\f'] = 1,
	['\v'] = 1,
};

int main(int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	char *file_name = argv[1];
	FILE *f = fopen(file_name, "rb");

	uint64_t words = 0;
	uint8_t in_word = 0;
	unsigned char buf[2048 * 2048];
	
	// hope the compiler will save this to a register
	const uint8_t *ws_tab = iswhitespace;

	for (;;) {
		size_t n = read(buf, 1, sizeof(buf), f);
		if (n == 0) break;

		const unsigned char *p  = buf;
		const unsigned char *end = buf + n;

		while (p < end) {
			unsigned char c = *p;
			uint8_t ws = ws_tab[c]; // 1 if c is whitespace
			p++;
			words += (uint64_t) ((!ws) & (!in_word));

			in_word = (!ws);
		}
	}

	printf("%" PRIu64 "\n", words);
	return 0;
}
