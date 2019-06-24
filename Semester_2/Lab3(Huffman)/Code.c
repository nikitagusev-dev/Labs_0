#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Code.h"
#define MAX_SIZE 256
#define FILLER 0

Code *newCode(unsigned char* sym, const int size) {
	Code *tmp = (Code*)malloc(sizeof(Code));
	tmp->sym = sym;
	tmp->size = size;
	return tmp;
}

void countFreq(int* freqTable, FILE *in) {
	int count;
	unsigned char *buffer = calloc(1024, sizeof(char));
	while (count = fread(buffer, sizeof(char), 1024, in)) {
		for (int i = 0; i < count; i++) {
			freqTable[buffer[i]]++;
		}
	}
	free(buffer);
}

void buildBase(queue **queue, int *freqTable) {
	for (int i = 0; i < MAX_SIZE; i++) {
		if (freqTable[i]) {
			push(queue, newtree(i, freqTable[i]));
		}
	}
}

static tree *merge(tree *first, tree *second) {
	tree *tmp = newtree(FILLER, first->freq + second->freq);
	tmp->left = second;
	tmp->right = first;
	return tmp;
}

tree *buildCodetree(queue **queue) {
	if (!(*queue)) {
		return NULL;
	}
	while ((*queue)->next) {
		push(queue, merge(pop(queue), pop(queue)));
	}
	return pop(queue);
}

void writeSize(const unsigned int size, FILE *out) {
	fwrite(&size, sizeof(unsigned int), 1, out);
}

static void writeBits(const unsigned char bits, const int count, BitStream *bitStream, FILE *out) {
	if (!count) {
		return;
	}
	int shift = CHAR_BIT - bitStream->size;
	if (shift >= count) {
		bitStream->size += count;
		bitStream->byte <<= count;
		unsigned char mask = (1 << count) - 1;
		bitStream->byte += bits & mask;
		if (bitStream->size == CHAR_BIT) {
			fputc(bitStream->byte, out);
			bitStream->size = 0;
			bitStream->byte = 0;
		}
		return;
	}
	writeBits(bits >> (count - shift), shift, bitStream, out);
	writeBits(bits, count - shift, bitStream, out);
}

void writetree(tree *codetree, BitStream *bitStream, FILE *out) {
	if (!codetree) {
		return;
	}
	if (!codetree->left) {
		writeBits(0, 1, bitStream, out);
		writeBits(codetree->sym, CHAR_BIT, bitStream, out);
		return;
	}
	writeBits(1, 1, bitStream, out);
	writetree(codetree->left, bitStream, out);
	writetree(codetree->right, bitStream, out);
}

static void resizeBuffer(Code *buffer) {
	buffer->size++;
	int isOverflow = buffer->size % CHAR_BIT;
	if (isOverflow == 1) {
		int bytes = buffer->size / CHAR_BIT + 1;
		buffer->sym = (unsigned char*)realloc(buffer->sym, bytes);
		buffer->sym[bytes - 1] = 0;
	}
}

static void addBit(Code *buffer, const int bit) {
	int pos = (buffer->size - 1) / CHAR_BIT;
	buffer->sym[pos] = (buffer->sym[pos] << 1) + bit;
}

static unsigned char* copyCode(Code *buffer) {
	int bytes = (buffer->size - 1) / CHAR_BIT + 1;
	unsigned char* newSym = (unsigned char*)malloc(bytes);
	for (int i = 0; i < bytes; i++) {
		newSym[i] = buffer->sym[i];
	}
	return newSym;
}

void buildCodeTable(Code **codeTable, tree *codetree, Code *buffer) {
	if (!codetree) {
		return;
	}
	if (!codetree->left) {
		if (!buffer->sym) {
			resizeBuffer(buffer);
		}
		codeTable[codetree->sym] = buffer;
	}
	else {
		resizeBuffer(buffer);
		Code *newBuff = newCode(copyCode(buffer), buffer->size);
		addBit(buffer, 0);
		addBit(newBuff, 1);
		buildCodeTable(codeTable, codetree->left, buffer);
		buildCodeTable(codeTable, codetree->right, newBuff);
	}
}

void codeText(FILE *in, FILE *out, Code **codeTable, BitStream *bitStream) {
	int c, i;
	while ((c = fgetc(in)) != EOF) {
		for (i = 0; i < codeTable[c]->size / CHAR_BIT; i++) {
			writeBits(codeTable[c]->sym[i], CHAR_BIT, bitStream, out);
		}
		writeBits(codeTable[c]->sym[i], codeTable[c]->size % CHAR_BIT, bitStream, out);
	}
	if (bitStream->size) {
		fputc(bitStream->byte << (CHAR_BIT - bitStream->size), out);
	}
}
