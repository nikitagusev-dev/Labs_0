#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct edge {
	int start;
	int end;
	unsigned int weight;
	char check;
}edge;

void q_sort(struct edge *a, int left, int right)
{
	int mid;
	int i = left;
	int j = right;

	mid = (i + j) / 2;

	do {
		while (a[i].weight < a[mid].weight) {
			i++;
		}
		while (a[j].weight > a[mid].weight) {
			j--;
		}
		if (i <= j) {
			struct edge temp = a[i];
			a[i] = a[j];
			a[j] = temp;

			i++;
			j--;
		}
	} while (i < j);

	if (left <= j) q_sort(a, left, j);
	if (i <= right) q_sort(a, i, right);
}

void checkAmount(int numberOfVertices, int numberOfEdges) {
	if (numberOfVertices < 0 || numberOfVertices > 5000) {
		printf("bad number of vertices");
		exit(0);
	}
	if (numberOfEdges < 0 || numberOfEdges > (numberOfVertices * (numberOfVertices + 1) / 2)) {
		printf("bad number of edges");
		exit(0);
	}
}

void checkEdge(int start, int end, int weight, int numberOfVertices) {
	if (start < 0 || start > numberOfVertices || end < 0 || end > numberOfVertices) {
		printf("bad vertex");
		exit(0);
	}
	if (weight < 0 || weight > INT_MAX) {
		printf("bad length");
		exit(0);
	}
}

void checkStringAmount(int stringCount, int numberOfEdges) {
	stringCount += 3;
	if (stringCount < (numberOfEdges + 3)) {
		printf("bad number of lines");
		exit(0);
	}
}

void checkSpanningTree(int *component, int numberOfVertices) {
	for (int i = 1; i < numberOfVertices; i++) {
		if (component[i] != component[i + 1]) {
			printf("no spanning tree");
			exit(0);
		}
	}
}

void printResult(int numberOfEdges, struct edge *arrayOfEdges) {
	for (int i = 0; i < numberOfEdges; i++) {
		if (arrayOfEdges[i].check == 1) {
			if (arrayOfEdges[i].start < arrayOfEdges[i].end) {
				printf("%d %d\n", arrayOfEdges[i].start, arrayOfEdges[i].end);
			}
			else {
				printf("%d %d\n", arrayOfEdges[i].end, arrayOfEdges[i].start);
			}
		}
	}
}

void clear(int *component, struct edge *arrayOfEdges) {
	free(component);
	free(arrayOfEdges);
}

int main() {
	int numberOfVertices = -1;
	int numberOfEdges = -1;
	int start = 0;
	int end = 0;
	unsigned int weight;
	int stringCount = 0;
	int *component;
	edge *arrayOfEdges;

	scanf("%d", &numberOfVertices);
	scanf("%d", &numberOfEdges);

	if (numberOfVertices == -1 || numberOfEdges == -1) {
		printf("bad number of lines");
		exit(0);
	}
	if (numberOfVertices == 0 & numberOfEdges == 0) {
		printf("no spanning tree");
		exit(0);
	}

	checkAmount(numberOfVertices, numberOfEdges);
	component = (int *)calloc(numberOfVertices + 2, sizeof(int));
	arrayOfEdges = (struct edge *)calloc(numberOfEdges, sizeof(struct edge));

	for (int i = 0; i < numberOfEdges; i++) {
		scanf("%d", &start);
		scanf("%d", &end);
		scanf("%u", &weight);
		if (start == 0 & end == 0) {
			printf("bad number of lines");
		}
		else {
			checkEdge(start, end, weight, numberOfVertices);
			arrayOfEdges[i].start = start;
			arrayOfEdges[i].end = end;
			arrayOfEdges[i].weight = weight;
			arrayOfEdges[i].check = 0;
			stringCount++;
		}
	}

	checkStringAmount(stringCount, numberOfEdges);
	
	for (int i = 1; i <= numberOfVertices; i++) {
		component[i] = i;
	}

	q_sort(arrayOfEdges, 0, numberOfEdges - 1);

	for (int i = 0; i < numberOfEdges; i++) {
		if (component[arrayOfEdges[i].start] != component[arrayOfEdges[i].end]) {
			int currentComponent = component[arrayOfEdges[i].end];
			for (int j = 1; j <= numberOfVertices; j++) {
				if (component[j] == currentComponent) {
					component[j] = component[arrayOfEdges[i].start];
				}
			}
			arrayOfEdges[i].check = 1;
		}
	}

	checkSpanningTree(component, numberOfVertices);
	printResult(numberOfEdges, arrayOfEdges);
	clear(component, arrayOfEdges);

	return 0;
}
