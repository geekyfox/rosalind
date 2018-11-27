#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rosalind.h"

static bool str_remove(char* haystack, const char* needle)
{
	int start = subs_search(haystack, needle);
	if (start == -1)
		return false;
	int x = strlen(haystack), y = strlen(needle);
	memmove(haystack + start, haystack + start + y, x - start - y + 1);
	return true;
}

void splc_solve(FILE* in, FILE* out)
{
	char* items[100];
	int item_count = fasta_read_payload(items, 100, 2, in);

	char* dna = items[0];

	bool flag=true;
	while (flag) {
		flag = false;
		for (int i=1; i<item_count;i++)
			flag = str_remove(dna, items[i]) || flag;
	}

	char rna[1024], protein[1024];
	rna_transcribe(rna, dna);
	prot_translate(protein, rna);
	fprintf(out, "%s\n", protein);

	for (int i=0; i<item_count; i++)
		free(items[i]);
}
