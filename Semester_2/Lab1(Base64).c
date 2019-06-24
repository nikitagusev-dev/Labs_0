#define _CRT_SECURE_NO_WARNINGS
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int identifySymbol(int* currentSymbol, const char* alphabet, int* eqSign) {
	if ((*currentSymbol > 'z') || (*currentSymbol < '+')) {
		return 1;
	}
	else if ((*currentSymbol >= '0') && (*currentSymbol <= '9')) {
		*currentSymbol = *currentSymbol - '0' + 52;
		return 0;
	}
	else if ((*currentSymbol >= 'a') && (*currentSymbol <= 'z')) {
		*currentSymbol = *currentSymbol - 'a' + 26;
		return 0;
	}
	else if ((*currentSymbol >= 'A') && (*currentSymbol <= 'Z')) {
		*currentSymbol = *currentSymbol - 'A';
		return 0;
	}
	else if (*currentSymbol == '+') {
		*currentSymbol = 62;
		return 0;
	}
	else if (*currentSymbol == '/') {
		*currentSymbol = 63;
		return 0;
	}
	else if (*currentSymbol == '=') {
		eqSign++;
		return 0;
	}
	return 0;
}

void decode(FILE* in, FILE* out, char* alphabet, int flag) {
	int error;
	int eqSign = 0;
	int currentSymbol;
	int count = 0;
	char buffer[5] = { 0 };

	while ((currentSymbol = fgetc(in)) != EOF) {
		error = identifySymbol(&currentSymbol, alphabet, &eqSign);
		if ((error == 1) && (flag == 0)) {
			printf("Unknown symbol in input file");
			fclose(in);
			fclose(out);
			exit(0);
		}
		buffer[count] = currentSymbol;
		count++;
		if ((error == 1) && (flag == 1))
			count--;
		if (count == 4) {
			fprintf(out, "%c", buffer[0] << 2 | buffer[1] >> 4);
			if (eqSign == 0) {
				fprintf(out, "%c", buffer[1] << 4 | buffer[2] >> 2);
				fprintf(out, "%c", buffer[2] << 6 | buffer[3]);
			}
			else if (eqSign == 1) {
				fprintf(out, "%c", buffer[1] << 4 | buffer[2] >> 2);
			}
			count = 0;
		}
	}
}

void encode(FILE* in, FILE* out, const char* alphabet) {
	unsigned char buffer[4] = { 0 };
	int currentSymbol;
	int count = 0;

	while ((currentSymbol = fgetc(in)) != EOF) {
		buffer[count] = currentSymbol;
		count++;
		if (count == 3) {
			fprintf(out, "%c", alphabet[(buffer[0] >> 2)]);
			fprintf(out, "%c", alphabet[(buffer[0] << 4) & 0x3F | (buffer[1]) >> 4]);
			fprintf(out, "%c", alphabet[(buffer[1] << 2) & 0x3F | (buffer[2] >> 6)]);
			fprintf(out, "%c", alphabet[buffer[2] & 0x3F]);
			count = 0;
			memset(buffer, 0, 3);
		}
	}
	if (count == 2) {
		fprintf(out, "%c", alphabet[(buffer[1] << 2) & 0x3F | (buffer[2] >> 6)]);
		fprintf(out, "%c", '=');
	}
	else if (count == 1) {
		fprintf(out, "%c", '=');
		fprintf(out, "%c", '=');
	}
}

void printHelpManual(void) {
	printf(
		"Base64 encode&decode v0.1 with flags, help and checking.\n-e to "
		"encode\n");
	printf("-d to decode\n-help to help message\n");
	printf("-d -i to decode with ignoring non-base64alph symbols\n");
	printf("-e -f N to encode with ENTER after N symbols\n");
	printf("Example: base64ed -d(-e) inputfile outputfile\n");
}

int main(int argc, char* argv[]) {
	char* infile = argv[argc - 2];
	char* outfile = argv[argc - 1];
	int count = 0;
	int ignFlag = 0;
	char alphabet[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	FILE* in;
	FILE* out = fopen(outfile, "wb");

	if (!(in = fopen(infile, "rb"))) {
		printf("File %s does not exist\n", infile);
		fclose(out);
		exit(0);
	}
	char flag;
	int e = 0, d = 0, f = 0, i = 0, h = 0;
	int flagError = 0;
	int symbol = 0;

	if ((!strcmp(argv[1], "--help")) || (h == 1)) {
		printHelpManual();
		fclose(in);
		exit(0);
	}

	while ((flag = getopt(argc, argv, "eidf:")) != -1) {
		switch (flag) {
		case ('e'):
			e = 1;
			break;
		case ('d'):
			d = 1;
			break;
		case ('i'):
			i = 1;
			break;
		case ('f'):
			if (optarg != 0) {
				f = 1;
				sscanf(optarg, "%d", &symbol);
			}
			break;
		default:
			flagError = 1;
			break;
		}
	}
	if (flagError == 1) {
		printf("flag error! print --help to help message\n");
		fclose(in);
		exit(0);
	}
	if ((symbol == 0) && (f == 1)) {
		printf("-f requires arg!\n");
		fclose(in);
		exit(0);
	}
	if ((f == 1) && (d == 1)) {
		printf("-f doesn't work with -d!\n");
		fclose(in);
		exit(0);
	}
	if ((d == 0) && (e == 0)) {
		printf("what do you want? print --help to help message\n");
		fclose(in);
		exit(0);
	}
	if ((e == 1) && (i == 1)) {
		printf("-i doesn't work with -e!\n");
		fclose(in);
		exit(0);
	}
	if (argc == 4) {
		if (e == 1) {
			encode(in, out, alphabet);
		}
		else if (d == 1) {
			decode(in, out, alphabet, ignFlag);
		}
	}
	if (argc > 4) {
		if ((e == 1) && (f == 1)) {
			encode(in, out, alphabet);
			fclose(out);
			int buffer;
			FILE* bufferFile = fopen("bufferFile.txt", "w");
			FILE* out = fopen(outfile, "r");
			while ((buffer = fgetc(out)) != EOF) {
				if (symbol == count) {
					fprintf(bufferFile, "\n");
					count = 0;
				}
				count++;
				fputc(buffer, bufferFile);
			}
			fclose(out);
			remove(outfile);
			fclose(bufferFile);
			int check2;
			check2 = rename("bufferFile.txt", outfile);
		}
		else {
			if ((d == 1) && (i == 1)) {
				ignFlag = 1;
				decode(in, out, alphabet, ignFlag);
			}
		}
	}
	fclose(in);
	if (count == 0)
		fclose(out);
	return 0;
}
