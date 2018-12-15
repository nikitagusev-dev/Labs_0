#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(char *a, int c, int b) {
	int temp = a[c];
	a[c] = a[b];
	a[b] = temp;
}

void sort(char *a, int b) {
	int s = 0;
	int len = strlen(a) - 1;
	while (b < len) {
		swap(a, b, len - s);
		b++;
		s++;
	}
}

void checkBadInput(char *a) {
	for (int i = 0; i < strlen(a) - 1; i++) {
		for (int j = i + 1; j < strlen(a); j++) {
			if (a[i] == a[j]) {
				printf("bad input");
				exit (0);
			}
		}
	}
	for (int i = 0; i < strlen(a); i++) {
		if (a[i] < '0' || a[i] > '9') {
			printf("bad input");
			exit(0);
		}
	}
}

int findMinElem(char *a, int i) {
	int min = i + 1;
	for (int j = i + 1; j < strlen(a); j++) {
		if ((a[j] > a[i]) && (a[j] < a[min])) {
			min = j;
		}
	}
	return min;
}

void printPermutation(char *a) {
	for (int i = 0; i < strlen(a); i++) {
		printf("%c", a[i]);
	}
	printf("\n");
}

void permutations(char *a, int N) {
	for (int s = 0; s < N; s++) {
		int len = strlen(a) - 1;
		int beforeLen = strlen(a) - 2;
		
		while (beforeLen >= 0) {
			if (a[beforeLen] < a[len]) {
				int min = findMinElem(a, beforeLen);
				swap(a, beforeLen, min);
				sort(a, beforeLen + 1);
				printPermutation(a);
				break;
			}
			beforeLen--;
			len--;
		}
	}
}

int main() {
	int N;
	char a[11] = { '\0' };
	
	gets(a);
	scanf("%d", &N);

	checkBadInput(a);
	permutations(a, N);

	return 0;
}
