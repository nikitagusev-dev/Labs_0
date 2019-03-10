#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct node {
	struct node *left;
	struct node *right;
	int height;
	int key;
};

int height(struct node *p) {
	return p ? p->height : 0;
}

int bfactor(struct node *p) {
	return height(p->right) - height(p->left);
}

void fixheight(struct node *p) {
	int heightLeft = height(p->left);
	int heightRight = height(p->right);
	p->height = ((heightLeft > heightRight) ? heightLeft : heightRight) + 1;
}

struct node *rotateRight(struct node *p) {
	struct node *q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

struct node *rotateLeft(struct node *p) {
	struct node *q = p->right;
	p->right = q->left;
	q->left = p;
	fixheight(p);
	fixheight(q);
	return q;
}

struct node *balance(struct node *p){
	fixheight(p);
	if (bfactor(p) == 2){
		if (bfactor(p->right) < 0)
			p->right = rotateRight(p->right);
		return rotateLeft(p);
	}
	if (bfactor(p) == -2){
		if (bfactor(p->left) > 0)
			p->left = rotateLeft(p->left);
		return rotateRight(p);
	}
	return p;
}

struct node *insert(struct node *p, int k) {
	if (!p) {
		p = malloc(sizeof(struct node));
		p->key = k;
		p->left = NULL;
		p->right = NULL;
		p->height = 1;
		return p;
	}
	if (k < p->key) {
		p->left = insert(p->left, k);
	}
	else {
		p->right = insert(p->right, k);
	}
	return balance(p);
}

void clear(struct node *p) {
	if (p) {
		if (p->left) {
			clear(p->left);
		}
		if (p->right) {
			clear(p->right);
		}
		free(p);
	}
}

int main() {
	int N = 0;
	int key = 0;
	scanf("%d", &N);
	struct node *root = NULL;
	if (N == 0) {
		printf("0");
		exit(0);
	}
	for (int i = 0; i < N; i++) {
		scanf("%d", &key);
		root = insert(root, key);
	}
	printf("%d", root -> height);
	clear(root);
	return 0;
}
