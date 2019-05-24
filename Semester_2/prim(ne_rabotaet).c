#define _CRT_SECURE_NO_WARNINGS
#define INF 1e9
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct edge {
	int start;
	int end;
	unsigned int weight;
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

void printResult(FILE *out, int minVertice, int endOfEdge) {
	if (minVertice > endOfEdge) {
		fprintf(out, "%d %d\n", endOfEdge, minVertice);
	}
	else {
		fprintf(out, "%d %d\n", minVertice, endOfEdge);
	}
}

void clear(int *dist, struct edge *arrayOfEdges) {
	free(dist);
	free(arrayOfEdges);
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
	int *dist;
	int *used;
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
	dist = (int *)calloc(numberOfVertices + 1, sizeof(int));
	used = (int *)calloc(numberOfVertices + 1, sizeof(int));
	arrayOfEdges = (struct edge *)calloc(numberOfEdges, sizeof(struct edge));

	for (int i = 0; i < numberOfEdges; i++) {
		if (fscanf(in, "%d %d %d", &start, &end, &weight) == EOF) {
			fprintf(out, "bad number of lines");
			fclose(in);
			fclose(out);
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

	q_sort(arrayOfEdges, 0, numberOfEdges - 1);

	for (int i = 1; i <= numberOfVertices; i++) {
		dist[i] = INF;
	}
	dist[arrayOfEdges[0].start] = -1;

	int printingCount = 0;
	for (int i = 1; i <= numberOfVertices; i++) {
		int minDist = INF;
		int minVertice = 0;
		bool check = 0;
		for (int j = 1; j <= numberOfVertices; j++) {
			if (!used[j] && dist[j] < minDist) {
				minDist = dist[j];
				minVertice = j;
				check = 1;
			}
		}
		if (check == 1) {
			printingCount++;
		}
		used[minVertice] = 1;
		int endOfEdge = 0;
		int distTillEnd = INF;
		for (int v = 0; v < numberOfEdges; v++) {
			if (arrayOfEdges[v].start == minVertice || arrayOfEdges[v].end == minVertice) {
				if (arrayOfEdges[v].start == minVertice/* && !used[arrayOfEdges[v].end]*/) {
					dist[arrayOfEdges[v].end] = min(dist[arrayOfEdges[v].end], arrayOfEdges[v].weight);
					if (dist[arrayOfEdges[v].end] < distTillEnd) {
						distTillEnd = dist[arrayOfEdges[v].end];
						endOfEdge = arrayOfEdges[v].end;
					}
				}
				else if (arrayOfEdges[v].end == minVertice/* && !used[arrayOfEdges[v].start]*/) {
					dist[arrayOfEdges[v].start] = min(dist[arrayOfEdges[v].start], arrayOfEdges[v].weight);
					if (dist[arrayOfEdges[v].start] < distTillEnd) {
						distTillEnd = dist[arrayOfEdges[v].start];
						endOfEdge = arrayOfEdges[v].start;
					}
				}
			}
		}
		if (endOfEdge) {
			printResult(out, minVertice, endOfEdge);
		}
	}

	if (printingCount != numberOfVertices && numberOfVertices != 1) {
		fclose(out);
		out = fopen("out.txt", "w");
		fprintf(out, "no spanning tree");
	}

	fclose(in);
	fclose(out);

	clear(dist, arrayOfEdges);

	return 0;
}
