#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the opperations
#define NOP '\0'
#define RIG '>'
#define LEF '<'
#define INC '+'
#define DEC '-'
#define OUT '.'
#define INN ','
#define OPN '['
#define CLS ']'

char Tokens[] = {
	RIG,
	LEF,
	INC,
	DEC,
	OUT,
	INN,
	OPN,
	CLS,
	NOP,
};

// Define the structure of a function
#define type char

// Read Source
char* Read (char* path, long* size) {
	FILE* fp = fopen(path, "r+");
	if (fp == NULL) { return NULL; }
	*size = fseek(fp, 0L, SEEK_END);
	if (*size != 0) { return NULL; }
	*size = ftell(fp);
	if (*size == 0) { return NULL; }
	rewind(fp);

	char* source = malloc(*size * sizeof(char));

	long rlen = 0;
	for (long i = 0; i < *size; i++) {
		char c = fgetc(fp);
		for (char k = 0; k < strlen(Tokens); k++) {
			if (c != Tokens[k]) { continue; }
			source[rlen] = c;
			rlen++;
			break;
		}
	}

	*size = rlen;
	
	source = (char*)realloc(source, sizeof(char)*rlen);

	fclose(fp);
	return source;
}

int main (int argc, char** argv) {
	if (argc < 1) return 1;
	char* path = argv[1];

	type mem[655360];
	long siz = 655360;
	type* ptr = mem;

	long e;
	char* txt = Read(path, &e);
	char* cmd = txt;
	char* end = txt+e;

	while (cmd != end) {
		char loops = 1;
		switch (*cmd) {
		case RIG:
			ptr++;
			break;
		case LEF:
			ptr--;
			break;
		case INC:
			*ptr += 1;
			break;
		case DEC:
			*ptr -= 1;
			break;
		case OPN:
			if (*ptr) break;
			while (loops) {
				cmd++;
				if (*cmd == OPN) loops++;
				else if (*cmd == CLS) loops--;
			}
		case CLS:
			if (!*ptr) break;
			while (loops) {
				cmd--;
				if (*cmd == OPN) loops--;
				else if (*cmd == CLS) loops++;
			}
			break;
		case OUT:
			putc(*ptr, stdout);
			break;
		case INN:
			*ptr = getc(stdin);
			break;
		default:
			break;
		}
		
		cmd++;
	}

	free(txt);
	return 0;
}

