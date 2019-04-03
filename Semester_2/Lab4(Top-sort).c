#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct stack {
	short element[1001];
	short top;
}stack;

void stackPush(struct stack *stk, short N){
	stk->element[stk->top] = N;
	stk->top++;
}

void stackPrint(struct stack *stk) {
	short curr;
	if (stk->top == 0) return;
	curr = stk->top - 1;
	while (curr >= 0) {
		printf("%hd ", stk->element[curr]);
		curr--;
	}
}

void DFS(short current, struct stack *stk, short **matrix, short *visited, short *count, short nodeCount) {
	visited[current] = 1;
	for (int i = 1; i <= count[current]; i++) {
		if (visited[matrix[current][i]] == 0) {
			DFS(matrix[current][i], stk, matrix, visited, count, nodeCount);
		}
		if (visited[matrix[current][i]] == 1) {
			printf("impossible to sort");
			exit(0);
		}
	}
	visited[current] = 2;
	stackPush(stk, current);
}

void doDFS(struct stack *stk, short **matrix, short *visited, short *count, short nodeCount) {
	for (int i = 1; i <= nodeCount; i++) {
		if (visited[i] == 0) {
			DFS(i, stk, matrix, visited, count, nodeCount);
		}
	}
}

void checkAmount(short numberOfNodes, int numberOfEdges) {
	if (numberOfNodes > 1000 || numberOfNodes < 0) {
		printf("bad number of vertices");
		exit(0);
	}
	if ((numberOfEdges < 0) || (numberOfEdges > (numberOfNodes * (numberOfNodes - 1) / 2))) {
		printf("bad number of edges");
		exit(0);
	}
}

void checkEdges(int first, int second, short numberOfNodes) {
	if (first < 1 || first > numberOfNodes || second < 1 || second > numberOfNodes) {
		printf("bad vertex");
		exit(0);
	}
}

void checkStringAmount(int stringCount, int numberOfEdges, short numberOfNodes) {
	if (numberOfNodes == 0) return;
	stringCount += 2;
	if (stringCount < numberOfEdges + 2) {
		printf("bad number of lines");
		exit(0);
	}
}

void clear(short **matrix, short *visited, short *count, struct stack *stk) {
	free(matrix);
	free(visited);
	free(count);
	free(stk);
}

int main() {
	short numberOfNodes = -1;
	int numberOfEdges = -1;
	int begin = 0;
	int end = 0;
	int stringCount = 0;
	short **matrix = NULL;
	stack *stk = NULL;
	short *visited = NULL;
	short *count = NULL;
		
	scanf("%d", &numberOfNodes);
	scanf("%d", &numberOfEdges);
	
	if (numberOfEdges == -1 || numberOfNodes == -1) {
		printf("bad number of lines");
		exit(0);
	}

	matrix = (short **)calloc((numberOfNodes + 1), sizeof(short *));
	stk = calloc(1, sizeof(stack));
	visited = (short *)calloc((numberOfNodes + 1), sizeof(short));
	count = (short *)calloc((numberOfNodes + 1), sizeof(short));
	
	for (int i = 0; i < numberOfEdges; i++) {
		scanf("%hd", &begin);
		scanf("%hd", &end);
		if (begin == 0 & end == 0) {
			break;
		}
		else {
			checkEdges(begin, end, numberOfNodes);
			count[begin]++;
			matrix[begin] = (short *)realloc(matrix[begin], sizeof(short) * (count[begin] + 1));
			matrix[begin][count[begin]] = end;
			stringCount++;
		}
	}
	
	checkStringAmount(stringCount, numberOfEdges, numberOfNodes);
	checkAmount(numberOfNodes, numberOfEdges);
			
	doDFS(stk, matrix, visited, count, numberOfNodes);
	stackPrint(stk);
	clear(matrix, visited, count, stk);

	return 0;
}
