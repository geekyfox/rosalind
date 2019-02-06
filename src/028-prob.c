#include <stdio.h>
#include <math.h>

#include "rosalind.h"

double prob_dna_with_gc_content_log(const char* dna, double gc_content)
{
	struct dna_bases_counts stats;
	int ats, cgs;

	dna_count_bases(&stats, dna);
	ats = stats.adenine + stats.thymine;
	cgs = stats.cytosine + stats.guanine;
	return ats * log(0.5 - gc_content/2) + cgs * log(gc_content/2);
}

double prob_dna_with_gc_content(const char* dna, double gc_content)
{
	return exp(prob_dna_with_gc_content_log(dna, gc_content));
}

double prob_dna_with_gc_content_log10(const char* dna, double gc_content)
{
	return prob_dna_with_gc_content_log(dna, gc_content) / log(10);
}

void prob_solve(FILE* in, FILE* out)
{
	char dna[128];
	io_readline(dna, 128, in, 0);

	double gc_content;
	while (fscanf(in, "%lf", &gc_content) == 1) {
		double r = prob_dna_with_gc_content_log10(dna, gc_content);
		fprintf(out, "%.3lf ", r);
	}
	fprintf(out, "\n");
}
