#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct edge {
	int start;
	int end;
	unsigned int weight;
}edge;

void checkAmount(FILE *in, FILE *out, int numberOfVertices, int numberOfEdges) {
	if (numberOfVertices < 0 || numberOfVertices > 5000) {
		fprintf(out, "bad number of vertices");
		fclose(in);
		fclose(out);
		exit(0);
	}
	if (numberOfEdges < 0 || numberOfEdges >(numberOfVertices * (numberOfVertices + 1) / 2)) {
		fprintf(out, "bad number of edges");
		fclose(in);
		fclose(out);
		exit(0);
	}
}

void checkEdge(FILE *in, FILE *out, int start, int end, int weight, int numberOfVertices) {
	if (start < 0 || start > numberOfVertices || end < 0 || end > numberOfVertices) {
		fprintf(out, "bad vertex");
		fclose(in);
		fclose(out);
		exit(0);
	}
	if (weight < 0 || weight > INT_MAX) {
		fprintf(out, "bad length");
		fclose(in);
		fclose(out);
		exit(0);
	}
}

void checkStringAmount(FILE *in, FILE *out, int stringCount, int numberOfEdges) {
	stringCount += 3;
	if (stringCount < (numberOfEdges + 3)) {
		fprintf(out, "bad number of lines");
		fclose(in);
		fclose(out);
		exit(0);
	}
}

void printResult(FILE *out, int currentVertice, int *endOfEdge) {
	if (currentVertice > endOfEdge[currentVertice]) {
		fprintf(out, "%d %d\n", endOfEdge[currentVertice], currentVertice);
	}
	else {
		fprintf(out, "%d %d\n", currentVertice, endOfEdge[currentVertice]);
	}
}

void clear(unsigned int *dist, struct edge *arrayOfEdges, int *used, int *endOfEdge) {
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
	unsigned int weight;
	int stringCount = 0;
	unsigned int *dist;
	int *used;
	int *endOfEdge;
	edge *arrayOfEdges;

	fscanf(in, "%d", &numberOfVertices);
	fscanf(in, "%d", &numberOfEdges);

	if (numberOfVertices == -1 || numberOfEdges == -1) {
		fprintf(out, "bad number of lines");
		fclose(in);
		fclose(out);
		exit(0);
	}
	if (numberOfVertices == 0 && numberOfEdges == 0) {
		fprintf(out, "no spanning tree");
		fclose(in);
		fclose(out);
		exit(0);
	}

	checkAmount(in, out, numberOfVertices, numberOfEdges);
	dist = (unsigned int *)calloc(numberOfVertices + 1, sizeof(unsigned int));
	used = (int *)calloc(numberOfVertices + 1, sizeof(int));
	endOfEdge = (int *)calloc(numberOfVertices + 1, sizeof(int));
	arrayOfEdges = (struct edge *)calloc(numberOfEdges, sizeof(struct edge));

	for (int i = 0; i < numberOfEdges; i++) {
		if (fscanf(in, "%d %d %u", &start, &end, &weight) == EOF) {
			fprintf(out, "bad number of lines");
			fclose(in);
			fclose(out);
			clear(dist, arrayOfEdges, used, endOfEdge);
			exit(0);
		}
		else {
			checkEdge(in, out, start, end, weight, numberOfVertices);
			arrayOfEdges[i].start = start;
			arrayOfEdges[i].end = end;
			arrayOfEdges[i].weight = weight;
			stringCount++;
		}
	}

	checkStringAmount(in, out, stringCount, numberOfEdges);

	for (int i = 1; i <= numberOfVertices; i++) {
		dist[i] = INT_MAX + 1;
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
			fclose(in);
			fclose(out);
			clear(dist, arrayOfEdges, used, endOfEdge);
			exit(0);
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
	
	fclose(in);
	fclose(out);

	clear(dist, arrayOfEdges, used, endOfEdge);
	
	return 0;
}
