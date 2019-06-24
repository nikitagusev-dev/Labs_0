#ifndef HUFFMAN_CODE_H
#define HUFFMAN_CODE_H
#include "Structs.h"

Code *newCode(unsigned char* sym, const int size);
void countFreq(int* freqTable, FILE *in);
void buildBase(queue **queue, int* freqTable);
tree *buildCodetree(queue **queue);
void writeSize(const unsigned int size, FILE *out);
void writetree(tree *codetree, BitStream *bitStream, FILE *out);
void buildCodeTable(Code **codeTable, tree *codetree, Code *buffer);
void codeText(FILE *in, FILE *out, Code **codeTable, BitStream *bitStream);

#endif
