#include <stdio.h>
#include <stdlib.h>
#include "Structs.h"

queue *newqueue(tree *node) {
	queue *tmp = (queue*)malloc(sizeof(queue));
	tmp->next = NULL;
	tmp->root = node;
	return tmp;
}

tree *newtree(const unsigned char sym, const int freq) {
	tree *tmp = (tree*)malloc(sizeof(tree));
	tmp->freq = freq;
	tmp->sym = sym;
	tmp->left = NULL;
	tmp->right = NULL;
	return tmp;
}

void push(queue **sortedqueue, tree *node) {
	int val = node->freq;
	queue *tmp = newqueue(node);
	if (!(*sortedqueue) || (*sortedqueue)->root->freq >= val) {
		tmp->next = *sortedqueue;
		*sortedqueue = tmp;
		return;
	}
	queue *cur = *sortedqueue;
	while (cur->next && val > cur->next->root->freq) {
		cur = cur->next;
	}
	tmp->next = cur->next;
	cur->next = tmp;
}

tree *pop(queue **head) {
	queue *tmp = *head;
	tree *sym = tmp->root;
	*head = (*head)->next;
	free(tmp);
	return sym;
}

BitStream *newBitStream(void) {
	BitStream *tmp = (BitStream*)malloc(sizeof(BitStream));
	tmp->byte = 0;
	tmp->size = 0;
	return tmp;
}
