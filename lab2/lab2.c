#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

char val[256]; // value

void table (unsigned char pattern[17]) {
	for (size_t i = 0; i <= 255; i++) {
		val[i] = strlen(pattern);
	}
	for (size_t i = 0; i < strlen(pattern) - 1; i++) {
		val[pattern[i]] = strlen(pattern) - i - 1;
	}	}

void protocol (unsigned char str[1000], unsigned char pattern[17]) {
	int textlen = strlen(str);
	int pattlen = strlen(pattern);
	int k, i, v;

	i = pattlen - 1;
	k = i;
	v = i;
		
	while (i <= textlen - 1) {
		k = pattlen - 1; 
		v = i;
		printf("%d ", v+1);
		while ((k > 0) && (str[v] == pattern[k])) {
			v--;
			k--;
			printf("%d ", v+1);
		}
		i += val[str[i]];
	}
}

int main() {
	unsigned char str[1000] = { 0 };
	unsigned char pattern[17];
	char input[128];

	gets(pattern);

	while (fgets(input, sizeof(input), stdin)) {
		strcat(str, input);
		if (input[0] == '\n')
			break;
	}

	if (str[0] && str[strlen(str) - 1] == '\n')
		str[strlen(str) - 1] = 0;

	table(pattern);
	protocol(str, pattern);

	return 0;
}
		 


