#ifndef HUFFMAN_CODE_H
#define HUFFMAN_CODE_H
#include "Structs.h"

queue *newqueue(tree *node);
tree *newtree(unsigned char sym, int freq);
Code *newCode(unsigned char* sym, int size);
void push(queue **sortedqueue, tree *node);
tree *pop(queue **head);
void countFreq(int* freqTable, FILE *in);
void buildBase(queue **queue, int* freqTable);
tree *merge(tree *first, tree *second);
tree *buildCodetree(queue **queue);
void writeSize(unsigned int size, FILE *out);
void writeBits(unsigned char bits, int count, BitStream *bitStream, FILE *out);
void writetree(tree *codetree, BitStream *bitStream, FILE *out);
void resizeBuffer(Code *buffer);
void addBit(Code *buffer, int bit);
unsigned char* copyCode(Code *buffer);
void buildCodeTable(Code **codeTable, tree *codetree, Code *buffer);
void codeText(FILE *in, FILE *out, Code **codeTable, BitStream *bitStream);

#endif
