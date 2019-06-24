#ifndef HUFFMAN_STRUCTS_H
#define HUFFMAN_STRUCTS_H

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

queue *newqueue(tree *node);
tree *newtree(const unsigned char sym, const int freq);
void push(queue **sortedqueue, tree *node);
tree *pop(queue **head);
BitStream *newBitStream(void);

#endif
