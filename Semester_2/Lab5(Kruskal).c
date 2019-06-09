#define _CRT_SECURE_NO_WARNINGS
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct edge {
	int start;
	int end;
	unsigned int weight;
	char check;
}edge;

int compare(const void *a, const void *b) {
	struct edge *graphA = (struct edge*) a;
	struct edge *graphB = (struct edge*) b;
	return (int)(graphA->weight - graphB->weight);
}

int checkAmount(int numberOfVertices, int numberOfEdges) {
	if (numberOfVertices < 0 || numberOfVertices > 5000) {
		printf("bad number of vertices");
		return 0;
	}
	if (numberOfEdges < 0 || numberOfEdges >(numberOfVertices * (numberOfVertices + 1) / 2)) {
		printf("bad number of edges");
		return 0;
	}
	return 1;
}

int checkEdge(int start, int end, unsigned int weight, int numberOfVertices) {
	if (start < 0 || start > numberOfVertices || end < 0 || end > numberOfVertices) {
		printf("bad vertex");
		return 0;
	}
	if (weight < 0 || weight > INT_MAX) {
		printf("bad length");
		return 0;
	}
	return 1;
}

int checkStringAmount(int stringCount, int numberOfEdges) {
	stringCount += 3;
	if (stringCount < (numberOfEdges + 3)) {
		printf("bad number of lines");
		return 0;
	}
	return 1;
}

int checkSpanningTree(int *component, int numberOfVertices) {
	for (int i = 1; i < numberOfVertices; i++) {
		if (component[i] != component[i + 1]) {
			printf("no spanning tree");
			return 0;
		}
	}
	return 1;
}

int checkWarnings(int numberOfVertices, int numberOfEdges) {
	if (numberOfVertices == -1 || numberOfEdges == -1) {
		printf("bad number of lines");
		return 0;
	}
	if (numberOfVertices == 0 && numberOfEdges == 0) {
		printf("no spanning tree");
		return 0;
	}
	return 1;
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

	if (!checkWarnings(numberOfVertices, numberOfEdges) || !checkAmount(numberOfVertices, numberOfEdges)) {
		goto END;
	}

	component = (int *)calloc(numberOfVertices + 1, sizeof(int));
	arrayOfEdges = (struct edge *)calloc(numberOfEdges, sizeof(struct edge));

	for (int i = 0; i < numberOfEdges; i++) {
		scanf("%d", &start);
		scanf("%d", &end);
		scanf("%u", &weight);
		if (start == 0 && end == 0) {
			printf("bad number of lines");
			clear(component, arrayOfEdges);
			goto END;
		}
		else {
			if (!checkEdge(start, end, weight, numberOfVertices)) {
				clear(component, arrayOfEdges);
				goto END;
			}
			arrayOfEdges[i].start = start;
			arrayOfEdges[i].end = end;
			arrayOfEdges[i].weight = weight;
			arrayOfEdges[i].check = 0;
			stringCount++;
		}
	}

	if (!checkStringAmount(stringCount, numberOfEdges)) {
		clear(component, arrayOfEdges);
		goto END;
	}

	for (int i = 1; i <= numberOfVertices; i++) {
		component[i] = i;
	}

	qsort(arrayOfEdges, (size_t)numberOfEdges, sizeof(struct edge), compare);

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

	if (!checkSpanningTree(component, numberOfVertices)) {
		clear(component, arrayOfEdges);
		goto END;
	}
	printResult(numberOfEdges, arrayOfEdges);
	clear(component, arrayOfEdges);

	END:
	return 0;
}
