#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hash(unsigned char *a, int l, int r) {
	int sum = 0;
	int t = 1;
	for (int i = l; i < r; i++) {
		sum = sum + (a[i] % 3) * t;
		t *= 3;
	}
	return sum;
}

int nextHash(unsigned char *a, int sum, int l, int r) {
	int t = 1;
	int hash;
	for (int i = l; i < r - 1; i++) {
		t *= 3;
	}
	hash = ((sum - (a[l - 1] % 3)) / 3) + a[r - 1] % 3 * t;
	return hash;
}

void printResult(unsigned char *a, unsigned char *b, int l, int r, int differ) {
	for (int i = l; i < r; i++) {
		printf("%d ", i + 1);
		if (a[i - differ] != b[i]) {
			break;
		}
	}
}

int main() {
	unsigned char pattern[17] = { '\0' };
	unsigned char str[1000] = { '\0' };
	char input[128];
	
	gets(pattern);
	while (fgets(input, sizeof(input), stdin)) {
		strcat(str, input);
		if (input[0] == '\n')
			break;
	}
	
	int patLen = strlen(pattern);
	int strLen = strlen(str);

	if (patLen > strLen) {
		printf("%d", 0);
	}

	int i = 0;
	int differ = 0;
	int counterHashPrint = 0;
	int patternHash = hash(pattern, 0, patLen);
	int strHash = hash(str, 0, patLen);
	
	while (i < strLen) {
		if (strHash == patternHash) {
			if (counterHashPrint == 0) {
				printf("%d ", strHash);
				counterHashPrint++;
			}			
			printResult(pattern, str, i, patLen, differ);
			i++;
			patLen++;
			differ++;
			strHash = nextHash(str, strHash, i, patLen);
		}
		else {
			i++;
			patLen++;
			differ++;
			strHash = nextHash(str, strHash, i, patLen);
		}
	}
	return 0;
}
