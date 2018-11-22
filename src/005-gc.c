#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "rosalind.h"

static double compute(const char* dna)
{
	struct dna_bases_counts counts;
	int gcs, total;
	
	dna_count_bases(&counts, dna);
	gcs = counts.guanine + counts.cytosine;
	total = gcs + counts.adenine + counts.thymine;
	return (gcs * 100.0) / total;
}

void gc_solve(FILE* in, FILE* out)
{
	struct fasta_pair items[16];
	int item_count = fasta_read(items, 16, 1, in);
	
	int best_index = 0;
	double best_value = compute(items[0].payload);
	
	for (int i=1; i<item_count; i++) {
		double value = compute(items[i].payload);
		if (value > best_value) {
			best_index = i;
			best_value = value;
		}
	}
	
	fprintf(out, "%s\n%0.4lf\n", items[best_index].label, best_value);
	fasta_free(items, item_count);
}

size_t fasta_read(struct fasta_pair* dst, size_t avail, size_t min, FILE* in)
{
	size_t fill = 0;
	char input[10240], accum[102400];
	accum[0] = '\0';
	while (fgets(input, 10240, in)) {
		if (! str_trim(input))
			continue;
		if (input[0] != '>') {
			strcat(accum, input);
			continue;
		}
		if (accum[0]) {
			dst[fill++].payload = strdup(accum);
			accum[0] = '\0';
		}
		if (fill >= avail) {
			fprintf(stderr, "Insufficient buffer in read_fasta()\n");
			exit(1);			
		}
		dst[fill].label = strdup(input + 1);
	}
	assert(accum[0]);
	dst[fill++].payload = strdup(accum);
	assert(fill >= min);
    	return fill;
}

size_t fasta_read_payload(char** dst, size_t avail, size_t min, FILE* in)
{
	struct fasta_pair tmp[avail];
	size_t count = fasta_read(tmp, avail, min, in);
	
	for (int i=0; i<count; i++) {
		dst[i] = tmp[i].payload;
		free(tmp[i].label);
	}
	
	return count;
}

void fasta_free(struct fasta_pair* pairs, size_t count)
{
	for (int i=count-1; i>=0; i--) {
		free(pairs[i].label);
		free(pairs[i].payload);
	}
}
