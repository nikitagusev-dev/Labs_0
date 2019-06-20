#ifndef HUFFMAN_CODEDECODE_H
#define HUFFMAN_CODEDECODE_H
#include "Code.h"
#include "Decode.h"

void code(FILE *in, FILE *out);
void decode(FILE *in, FILE *out);
void freeCodeTable(Code **codeTable);
void freetree(tree *tree);

#endif
