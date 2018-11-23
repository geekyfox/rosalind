#include <stdlib.h>
#include <string.h>

#include "rosalind.h"

static int solve(int** memo, const char* rna, int first, int last)
{
	if (first > last)
		return 1;
	if (memo[first][last] >= 0)
		return memo[first][last];

	struct rna_bases_counts counts;
	bzero(&counts, sizeof(struct rna_bases_counts));

	int result=0;
	for (int i=first; i<=last; i++) {
		rna_increment_bases_count(&counts, rna[i]);
		if (counts.adenine != counts.uracil)
			continue;
		if (counts.cytosine != counts.guanine)
			continue;
		int p = solve(memo, rna, first+1, i-1);
		int q = solve(memo, rna, i+1, last);
		modulo_increment(&result, modulo_multiply(p, q));
	}
	memo[first][last] = result;
	return result;
}

void cat_solve(FILE* in, FILE* out)
{
	char* rna = fasta_read_payload_single(in);

	int len = strlen(rna);
	int** m = matrix_init(len, len, -1);
	int result = solve(m, rna, 0, len-1);
	fprintf(out, "%d\n", result);

	matrix_free(m);
	free(rna);
}

int** matrix_alloc(int rows, int cols)
{
	int** m = malloc(sizeof(int*) * rows);
	m[0] = malloc(sizeof(int) * rows * cols);
	for (int i=rows-1; i>0; i--)
		m[i] = m[0] + i * cols;
	return m;
}

int** matrix_init(int rows, int cols, int fill)
{
	int** m = matrix_alloc(rows, cols);
	for (int i=rows-1; i>=0; i--)
		for (int j=cols-1; j>=0; j--)
			m[i][j] = fill;
	return m;
}

void matrix_free(int** m)
{
	free(m[0]);
	free(m);
}

int modulo_add(int x, int y)
{
	return (x + y) % 1000000;
}

void modulo_increment(int *ptr, int x)
{
	*ptr = modulo_add(*ptr, x);
}
