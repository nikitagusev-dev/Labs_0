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

void checkEdge(FILE *in, FILE *out, int start, int end, unsigned int weight, int numberOfVertices) {
	if (start < 1 || start > numberOfVertices || end < 1 || end > numberOfVertices) {
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
	stringCount += 4;
	if (stringCount < (numberOfEdges + 3)) {
		fprintf(out, "bad number of lines");
		fclose(in);
		fclose(out);
		exit(0);
	}
}

void calculateDistances(int numberOfVertices, int numberOfEdges, unsigned long long *dist, int *used, edge *arrayOfEdges) {
	for (int i = 1; i <= numberOfVertices; i++) {
		int currentVertice = -1;
		for (int j = 1; j <= numberOfVertices; j++) {
			if (!used[j] && (currentVertice == -1 || dist[j] < dist[currentVertice])) {
				currentVertice = j;
			}
		}
		used[currentVertice] = 1;
		unsigned long long temp;
		for (int v = 0; v < numberOfEdges; v++) {
			if (arrayOfEdges[v].start == currentVertice || arrayOfEdges[v].end == currentVertice) {
				temp = dist[currentVertice] + arrayOfEdges[v].weight;
				if (arrayOfEdges[v].start == currentVertice) {
					if (temp < dist[arrayOfEdges[v].end]) {
						dist[arrayOfEdges[v].end] = temp;
					}
				}
				else {
					if (temp < dist[arrayOfEdges[v].start]) {
						dist[arrayOfEdges[v].start] = temp;
					}
				}
			}
		}
	}
}

void printDistances(FILE *in, FILE *out, int numberOfVertices, int numberOfEdges, int beginOfWay, int endOfWay, unsigned long long *dist) {
	if (numberOfVertices != 0 && numberOfEdges == 0 && beginOfWay != endOfWay) {
		for (int i = 1; i <= numberOfVertices; i++) {
			if (dist[i] == INT_MAX + 1) {
				fprintf(out, "oo ");
			}
			else {
				fprintf(out, "%llu ", dist[i]);
			}
		}
		fprintf(out, "\n");
		fprintf(out, "no path");
		fclose(in);
		fclose(out);
		exit(0);
	}
	else {
		for (int i = 1; i <= numberOfVertices; i++) {
			if (dist[i] <= INT_MAX) {
				fprintf(out, "%llu ", dist[i]);
			}
			else if (dist[i] == (INT_MAX + 1)) {
				fprintf(out, "oo ");
			}
			else {
				fprintf(out, "INT_MAX+ ");
			}
		}
		fprintf(out, "\n");
	}
}

void calculatePath(FILE *out, int beginOfWay, int endOfWay, int numberOfEdges, edge *arrayOfEdges, int *verticesOfWay, unsigned long long *dist) {
	int wayVertice = endOfWay;
	unsigned long long currentWeight;
	verticesOfWay[0] = wayVertice;
	int index = 1;
	int overflowFlag = 0;
	int tempVertice;

	while (wayVertice != beginOfWay) {
		int check = 0;
		for (int i = 0; i < numberOfEdges; i++) {
			if (arrayOfEdges[i].start == wayVertice || arrayOfEdges[i].end == wayVertice) {
				currentWeight = dist[wayVertice] - arrayOfEdges[i].weight;
				if (arrayOfEdges[i].start == wayVertice) {
					if (currentWeight == dist[arrayOfEdges[i].end]) {
						tempVertice = arrayOfEdges[i].end;
						if (check == 0) {
							verticesOfWay[index] = tempVertice;
							index++;
						}
						if (check >= 1) {
							verticesOfWay[index - 1] = tempVertice;
						}
						check++;
					}
				}
				else {
					if (currentWeight == dist[arrayOfEdges[i].start]) {
						tempVertice = arrayOfEdges[i].start;
						if (check == 0) {
							verticesOfWay[index] = tempVertice;
							index++;
						}
						check++;
					}
				}
			}
		}
		wayVertice = tempVertice;
		if (check >= 2) {
			overflowFlag = 1;
		}
	}
	if (dist[endOfWay] > INT_MAX && overflowFlag == 1) {
		fprintf(out, "overflow");
	}
	else {
		for (int i = 0; i < index; i++) {
			fprintf(out, "%d ", verticesOfWay[i]);
		}
	}
}

void clear(unsigned int *dist, edge *arrayOfEdges, int *used, int *endOfEdge) {
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
	int beginOfWay;
	int endOfWay;
	int start = 0;
	int end = 0;
	unsigned int weight;
	int stringCount = 0;
	unsigned long long *dist;
	int *used;
	int *verticesOfWay;
	edge *arrayOfEdges;

	fscanf(in, "%d", &numberOfVertices);
	fscanf(in, "%d %d", &beginOfWay, &endOfWay);
	fscanf(in, "%d", &numberOfEdges);

	if (numberOfVertices == -1 || numberOfEdges == -1) {
		fprintf(out, "bad number of lines");
		fclose(in);
		fclose(out);
		exit(0);
	}

	checkAmount(in, out, numberOfVertices, numberOfEdges);
	dist = (unsigned long long *)calloc(numberOfVertices + 1, sizeof(unsigned long long));
	used = (int *)calloc(numberOfVertices + 1, sizeof(int));
	verticesOfWay = (int *)calloc(numberOfVertices, sizeof(int));
	arrayOfEdges = (struct edge *)calloc(numberOfEdges, sizeof(struct edge));

	for (int i = 0; i < numberOfEdges; i++) {
		if (fscanf(in, "%d %d %u", &start, &end, &weight) == EOF) {
			fprintf(out, "bad number of lines");
			fclose(in);
			fclose(out);
			clear(dist, arrayOfEdges, used, verticesOfWay);
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

	if (start == 0 && end == 0 && numberOfVertices == 0) {
		fprintf(out, "bad vertex");
		fclose(in);
		fclose(out);
		exit(0);
	}

	checkStringAmount(in, out, stringCount, numberOfEdges);

	for (int i = 1; i <= numberOfVertices; i++) {
		dist[i] = INT_MAX + 1;
	}
	dist[beginOfWay] = 0;

	calculateDistances(numberOfVertices, numberOfEdges, dist, used, arrayOfEdges);

	printDistances(in, out, numberOfVertices, numberOfEdges, beginOfWay, endOfWay, dist);

	calculatePath(out, beginOfWay, endOfWay, numberOfEdges, arrayOfEdges, verticesOfWay, dist);
		
	fclose(in);
	fclose(out);

	clear(dist, arrayOfEdges, used, verticesOfWay);

	return 0;
}
