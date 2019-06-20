#include "CodeDecode.h"

int main() {
	FILE *in = fopen("in.txt", "rb");
	FILE *out = fopen("out.txt", "wb");
	unsigned char mode = fgetc(in);
	fseek(in, 3, SEEK_SET);
	if (mode == 'c') {
		code(in, out);
	}
	else if (mode == 'd') {
		decode(in, out);
	}
	fclose(in);
	fclose(out);
	return 0;
}
