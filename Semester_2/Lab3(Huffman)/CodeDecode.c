#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "CodeDecode.h"
#define MAX_SIZE 256

static void freeCodeTable(Code **codeTable) {
	for (int i = 0; i < MAX_SIZE; i++) {
		if (codeTable[i]) {
			free(codeTable[i]->sym);
			free(codeTable[i]);
		}
	}
}

static void freetree(tree *tree) {
	if (!tree) {
		return;
	}
	if (tree->left) {
		freetree(tree->left);
	}
	if (tree->right) {
		freetree(tree->right);
	}
	free(tree);
}

void code(FILE *in, FILE *out) {
	int freqTable[MAX_SIZE];
	queue *queue = NULL;
	Code *codeTable[MAX_SIZE];
	tree *codetree = NULL;
	BitStream *bitStream = newBitStream();
	memset(freqTable, 0, sizeof(int) * MAX_SIZE);
	memset(codeTable, 0, sizeof(Code*) * MAX_SIZE);
	countFreq(freqTable, in);
	buildBase(&queue, freqTable);
	codetree = buildCodetree(&queue);
	if (codetree) {
		writeSize(codetree->freq, out);
	}
	writetree(codetree, bitStream, out);
	buildCodeTable(codeTable, codetree, newCode(NULL, 0));
	fseek(in, 3, SEEK_SET);
	codeText(in, out, codeTable, bitStream);
	free(bitStream);
	freeCodeTable(codeTable);
	freetree(codetree);
}

void decode(FILE *in, FILE *out) {
	unsigned int size;
	if (!readSize(in, &size)) {
		return;
	}
	BitStream *bitStream = newBitStream();
	tree *codetree = getCodetree(in, bitStream);
	decodeText(codetree, in, out, size, bitStream);
	free(bitStream);
	freetree(codetree);
}
