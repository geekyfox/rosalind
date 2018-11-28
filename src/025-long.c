#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "rosalind.h"

static int max_prefix(const char* haystack, const char* prefix)
{
	int match = 0, offset = 0, max_match = 0;

	while (prefix[match] && haystack[match + offset])
		if (prefix[match] == haystack[match + offset]) {
			match++;
			if (match > max_match)
				max_match = match;
		} else {
			match = 0;
			offset++;
		}

	return max_match;
}

static bool match(const char* prev, const char* next)
{
	if (prev == next)
		return false;
	int overlap = max_prefix(prev, next);
	return (overlap * 2) > strlen(prev);
}

static void swap(char** lines, int i, int j)
{
	char* t = lines[i];
	lines[i] = lines[j];
	lines[j] = t;
}

void long_solve(FILE* in, FILE* out)
{
	char* lines[64];
	char result[51200];

	int line_ct = fasta_read_payload(lines, 64, 0, in);

	for (int i=1; i<line_ct; i++) {
		bool is_first = true;
		for (int j=0; j<line_ct; j++) {
			if (match(lines[j], lines[i])) {
				is_first = false;
				break;
			}
		}
		if (is_first) {
			swap(lines, i, 0);
			break;
		}
	}

	for (int i=0; i<line_ct-1; i++) {
		if (match(lines[i], lines[i+1]))
			continue;
		for (int j=i+2; j<line_ct; j++)
			if (match(lines[i], lines[j])) {
				swap(lines, i+1, j);
				break;
			}
	}

	strcpy(result, lines[0]);
	for (int i=1; i<line_ct; i++) {
		int q = max_prefix(result, lines[i]);
		strcat(result, lines[i] + q);
	}
	fprintf(out, "%s\n", result);
	for (int i=0; i<line_ct; i++)
		free(lines[i]);
}
