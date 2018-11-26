#include <stdio.h>
#include <stdlib.h>

#include "rosalind.h"

static int count_options(char aminoacid)
{
    int count = 0;
    for (int i=0; i<64; i++)
        if (CODON_TABLE[i][3] == aminoacid)
            count++;
	if (count == 0) {
		fprintf(stderr, "Bad aminoacid: '%c'\n", aminoacid);
		exit(1);
	}
    return count;
}

void mrna_solve(FILE* in, FILE* out)
{
	char protein[1024];
	io_readline(protein, 1024, in, 0);
	long result = count_options('!');
	for (int i=0; protein[i]; i++)
		result = modulo_multiply(result, count_options(protein[i]));
	fprintf(out, "%ld\n", result);
}

int modulo_multiply(int x, int y)
{
	long long lx = (long long)x;
	long long ly = (long long)y;
	long long lz = (lx * ly) % 1000000;

	return (int)lz;
}
