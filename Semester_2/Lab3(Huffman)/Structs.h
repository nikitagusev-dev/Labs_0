#ifndef HUFFMAN_STRUCTS_H
#define HUFFMAN_STRUCTS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 256
#define FILLER 0

typedef struct tree {
	unsigned char sym;
	unsigned int freq;
	struct tree *left;
	struct tree *right;
} tree;

typedef struct queue {
	tree *root;
	struct queue *next;
} queue;

typedef struct Code {
	unsigned char* sym;
	int size;
} Code;

typedef struct BitStream {
	unsigned char byte;
	int size;
} BitStream;

BitStream *newBitStream();

#endif
