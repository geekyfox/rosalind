#include "rosalind.h"

void rna_solve(FILE* in, FILE* out)
{
	char dna[1024], rna[1024];

	io_readline(dna, 1024, in, 0);
	rna_transcribe(rna, dna);
	fprintf(out, "%s\n", rna);
}

void rna_transcribe(char* rna, const char* dna)
{
	for (; *dna; dna++, rna++)
		*rna = (*dna == 'T') ? 'U' : *dna;
	*rna = '\0';
}
