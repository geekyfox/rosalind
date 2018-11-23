#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "rosalind.h"

static char pick(struct dna_bases_counts counts)
{
	int max = counts.adenine;
	char result = 'A';
	if (max < counts.cytosine) {
		max = counts.cytosine;
		result = 'C';
	}
	if (max < counts.guanine) {
		max = counts.guanine;
		result = 'G';
	}
	if (max < counts.thymine) {
		max = counts.thymine;
		result = 'T';
	}
	return result;
}

static void printout(FILE *out, struct dna_bases_counts *profile, size_t len)
{
	fprintf(out, "A:");
	for (int i=0; i<len; i++)
		fprintf(out, " %d", profile[i].adenine);
	fprintf(out, "\n");

	fprintf(out, "C:");
	for (int i=0; i<len; i++)
		fprintf(out, " %d", profile[i].cytosine);
	fprintf(out, "\n");

	fprintf(out, "G:");
	for (int i=0; i<len; i++)
		fprintf(out, " %d", profile[i].guanine);
	fprintf(out, "\n");

	fprintf(out, "T:");
	for (int i=0; i<len; i++)
		fprintf(out, " %d", profile[i].thymine);
	fprintf(out, "\n");
}

void cons_solve(FILE* in, FILE* out)
{
	char* dnas[10];
	int count = fasta_read_payload(dnas, 10, 1, in);
	int len = strlen(dnas[0]);

	struct dna_bases_counts profile[1024];
	bzero(profile, sizeof(profile));

	char consensus[1024];
	for (int ix=0; ix<count; ix++) {
		char* dna = dnas[ix];
		for (int pos=0; pos<len; pos++)
			dna_increment_bases_count(&profile[pos], dna[pos]);
		free(dna);
	}
	for (int pos=0; pos<len; pos++)
		consensus[pos] = pick(profile[pos]);
	consensus[len] = '\0';

	fprintf(out, "%s\n", consensus);
	printout(out, profile, len);
}
