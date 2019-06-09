#define _CRT_SECURE_NO_WARNINGS
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct edge {
	int start;
	int end;
	long long weight;
}edge;

int checkAmount(FILE *out, int numberOfVertices, int numberOfEdges) {
	if (numberOfVertices < 0 || numberOfVertices > 5000) {
		fprintf(out, "bad number of vertices");
		return 0;
	}
	if (numberOfEdges < 0 || numberOfEdges > (numberOfVertices * (numberOfVertices + 1) / 2)) {
		fprintf(out, "bad number of edges");
		return 0;
	}
	return 1;
}

int checkEdge(FILE *out, int start, int end, long long weight, int numberOfVertices) {
	if (start < 0 || start > numberOfVertices || end < 0 || end > numberOfVertices) {
		fprintf(out, "bad vertex");
		return 0;
	}
	if (weight < 0 || weight > INT_MAX) {
		fprintf(out, "bad length");
		return 0;
	}
	return 1;
}

int checkStringAmount(FILE *out, int stringCount, int numberOfEdges) {
	stringCount += 3;
	if (stringCount < (numberOfEdges + 3)) {
		fprintf(out, "bad number of lines");
		return 0;
	}
	return 1;
}

int checkWarnings(FILE *out, int numberOfVertices, int numberOfEdges) {
	if (numberOfVertices == -1 || numberOfEdges == -1) {
		fprintf(out, "bad number of lines");
		return 0;
	}
	if (numberOfVertices == 0 && numberOfEdges == 0) {
		fprintf(out, "no spanning tree");
		return 0;
	}
	return 1;
}

void printResult(FILE *out, int currentVertice, int *endOfEdge) {
	if (currentVertice > endOfEdge[currentVertice]) {
		fprintf(out, "%d %d\n", endOfEdge[currentVertice], currentVertice);
	}
	else {
		fprintf(out, "%d %d\n", currentVertice, endOfEdge[currentVertice]);
	}
}

void clear(long long *dist, struct edge *arrayOfEdges, int *used, int *endOfEdge) {
	free(dist);
	free(arrayOfEdges);
	free(used);
	free(endOfEdge);
}

int main() {
	FILE *in = fopen("in.txt", "r");
	FILE *out = fopen("out.txt", "w");
	int numberOfVertices = -1;
	int numberOfEdges = -1;
	int start = 0;
	int end = 0;
	long long weight;
	int stringCount = 0;
	long long *dist;
	int *used;
	int *endOfEdge;
	edge *arrayOfEdges;

	fscanf(in, "%d", &numberOfVertices);
	fscanf(in, "%d", &numberOfEdges);

	if (!checkWarnings(out, numberOfVertices, numberOfEdges) || !checkAmount(out, numberOfVertices, numberOfEdges)) {
		goto END;
	}
	
	dist = (long long *)calloc(numberOfVertices + 1, sizeof(long long));
	used = (int *)calloc(numberOfVertices + 1, sizeof(int));
	endOfEdge = (int *)calloc(numberOfVertices + 1, sizeof(int));
	arrayOfEdges = (struct edge *)calloc(numberOfEdges, sizeof(struct edge));

	for (int i = 0; i < numberOfEdges; i++) {
		if (fscanf(in, "%d %d %lli", &start, &end, &weight) == EOF) {
			fprintf(out, "bad number of lines");
			clear(dist, arrayOfEdges, used, endOfEdge);
			goto END;
		}
		else {
			if (!checkEdge(out, start, end, weight, numberOfVertices)) {
				clear(dist, arrayOfEdges, used, endOfEdge);
				goto END;
			}
			arrayOfEdges[i].start = start;
			arrayOfEdges[i].end = end;
			arrayOfEdges[i].weight = weight;
			stringCount++;
		}
	}

	if (!checkStringAmount(out, stringCount, numberOfEdges)) {
		clear(dist, arrayOfEdges, used, endOfEdge);
		goto END;
	}

	for (int i = 1; i <= numberOfVertices; i++) {
		dist[i] = UINT_MAX;
	}
	dist[1] = 0;

	for (int i = 1; i <= numberOfVertices; i++) {
		int currentVertice = -1;
		for (int j = 1; j <= numberOfVertices; j++) {
			if (!used[j] && (currentVertice == -1 || dist[j] < dist[currentVertice])) {
				currentVertice = j;
			}
		}
		if (dist[currentVertice] > INT_MAX || currentVertice == -1) {
			fclose(out);
			out = fopen("out.txt", "w");
			fprintf(out, "no spanning tree");
			clear(dist, arrayOfEdges, used, endOfEdge);
			goto END;
		}
		used[currentVertice] = 1;
		if (endOfEdge[currentVertice] != 0) {
			printResult(out, currentVertice, endOfEdge);
		}
		for (int v = 0; v < numberOfEdges; v++) {
			if (arrayOfEdges[v].start == currentVertice || arrayOfEdges[v].end == currentVertice) {
				if (arrayOfEdges[v].start == currentVertice && arrayOfEdges[v].weight < dist[arrayOfEdges[v].end]) {
					dist[arrayOfEdges[v].end] = arrayOfEdges[v].weight;
					endOfEdge[arrayOfEdges[v].end] = currentVertice;
				}
				else if (arrayOfEdges[v].end == currentVertice && arrayOfEdges[v].weight < dist[arrayOfEdges[v].start]) {
					dist[arrayOfEdges[v].start] = arrayOfEdges[v].weight;
					endOfEdge[arrayOfEdges[v].start] = currentVertice;
				}				
			}
		}
	}
	
	clear(dist, arrayOfEdges, used, endOfEdge);

END:
	fclose(in);
	fclose(out);
	return 0;
}
