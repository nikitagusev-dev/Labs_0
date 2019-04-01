#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct stack {
	int element[1001];
	int top;
}stack;

void stackPush(struct stack *stk, int N){
	stk->element[stk->top] = N;
	stk->top++;
}

void stackPrint(struct stack *stk) {
	int curr;
	if (stk->top == 0) return;
	curr = stk->top - 1;
	while (curr >= 0) {
		printf("%d ", stk->element[curr]);
		curr--;
	}
}

void DFS(int current, struct stack *stk, int **matrix, int *visited, int nodeCount) {
	visited[current] = 1;
	for (int i = 1; i <= nodeCount; i++) {
		if (matrix[current][i] == 1) {
			if (visited[i] == 0) {
				DFS(i, stk, matrix, visited, nodeCount);
			}
			if (visited[i] == 1) {
				printf("impossible to sort");
				exit(0);
			}
		}
	}
	visited[current] = 2;
	stackPush(stk, current);
}

void doDFS(struct stack *stk, int **matrix, int *visited, int nodeCount) {
	for (int i = 1; i <= nodeCount; i++) {
		if (visited[i] == 0) {
			DFS(i, stk, matrix, visited, nodeCount);
		}
	}
}

void checkAmount(int numberOfNodes, int numberOfEdges) {
	if (numberOfNodes > 1000 || numberOfNodes < 0) {
		printf("bad number of vertices");
		exit(0);
	}
	if (numberOfEdges < 0 || numberOfEdges > (numberOfNodes * (numberOfNodes - 1) / 2)) {
		printf("bad number of edges");
		exit(0);
	}
}

void checkEdges(int first, int second, int numberOfNodes) {
	if (first < 1 || first > numberOfNodes || second < 1 || second > numberOfNodes) {
		printf("bad vertex");
		exit(0);
	}
}

void checkStringAmount(int stringCount, int numberOfEdges, int numberOfNodes) {
	if (numberOfNodes == 0) return;
	stringCount += 2;
	if (stringCount < numberOfEdges + 2) {
		printf("bad number of lines");
		exit(0);
	}
}

int main() {
	int numberOfNodes = -1;
	int numberOfEdges = -1;
	int begin = 0;
	int end = 0;
	int stringCount = 0;
	int **matrix = NULL;
	stack *stk = NULL;
	int *visited = NULL;
		
	scanf("%d", &numberOfNodes);
	scanf("%d", &numberOfEdges);
	
	if (numberOfEdges == -1 || numberOfNodes == -1) {
		printf("bad number of lines");
		exit(0);
	}

	matrix = (int **)malloc((numberOfNodes + 1) * sizeof(int *));
	for (int i = 0; i <= numberOfNodes; i++) {
		matrix[i] = (int *)malloc((numberOfNodes + 1) * sizeof(int));
	}
	stk = calloc(1, sizeof(stack));
	visited = (int *)malloc((numberOfNodes + 1) * sizeof(int));
	
	for (int i = 0; i <= numberOfNodes; i++) {
		matrix[i][i] = 0;
		visited[i] = 0;
	}
	for (int i = 0; i < numberOfEdges; i++) {
		scanf("%d", &begin);
		scanf("%d", &end);
		if (begin == 0 & end == 0) {
			break;
		}
		else {
			checkEdges(begin, end, numberOfNodes);
			stringCount++;
			matrix[begin][end] = 1;
		}
	}
	checkStringAmount(stringCount, numberOfEdges, numberOfNodes);
	checkAmount(numberOfNodes, numberOfEdges);
			
	doDFS(stk, matrix, visited, numberOfNodes);
	stackPrint(stk);

	return 0;
}
