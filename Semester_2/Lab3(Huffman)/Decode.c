#include "Decode.h"

int readSize(FILE *in, unsigned int* size) {
	return fread(size, sizeof(unsigned int), 1, in);
}

unsigned char getBit(BitStream *bitStream, FILE *in) {
	if (!bitStream->size) {
		bitStream->byte = fgetc(in);
		bitStream->size = CHAR_BIT;
	}
	unsigned char bit = bitStream->byte >> 7;
	bitStream->size--;
	bitStream->byte <<= 1;
	return bit;
}

tree *getCodetree(FILE *in, BitStream *bitStream) {
	tree *codetree = NULL;
	if (getBit(bitStream, in)) {
		codetree = newtree(FILLER, FILLER);
		codetree->left = getCodetree(in, bitStream);
		codetree->right = getCodetree(in, bitStream);
	}
	else {
		unsigned char sym = 0;
		for (int i = 0; i < CHAR_BIT; i++) {
			sym = (sym << 1) + getBit(bitStream, in);
		}
		codetree = newtree(sym, FILLER);
	}
	return codetree;
}

void decodeText(tree *codetree, FILE *in, FILE *out, unsigned int size, BitStream *bitStream) {
	tree *tmpCodetree;
	for (unsigned int i = 0; i < size; i++) {
		tmpCodetree = codetree;
		while (tmpCodetree->left) {
			if (getBit(bitStream, in)) {
				tmpCodetree = tmpCodetree->right;
			}
			else {
				tmpCodetree = tmpCodetree->left;
			}
		}
		fputc(tmpCodetree->sym, out);
	}
}
