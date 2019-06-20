#ifndef HUFFMAN_DECODE_H
#define HUFFMAN_DECODE_H
#include "Structs.h"

int readSize(FILE *in, unsigned int *size);
unsigned char getBit(BitStream *bitStream, FILE *in);
tree *getCodetree(FILE *in, BitStream *bitStream);
void decodeText(tree *codetree, FILE *in, FILE *out, unsigned int size, BitStream *bitStream);

#endif
