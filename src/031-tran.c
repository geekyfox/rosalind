#include <stdio.h>
#include <stdlib.h>

#include "rosalind.h"

void tran_solve(FILE* in, FILE* out)
{
	char *first, *second;
	fasta_read_payload_pair(&first, &second, in);

	int transitions = 0, transversions = 0;
	for (int i=0; first[i]; i++) {
		char x = first[i];
		char y = second[i];
		if (x == y)
			continue;
		if (x > y) {
			char t = x;
			x = y;
			y = t;
		}
		if ((x == 'A') && (y == 'G')) {
			transitions++;
		}  else if ((x == 'C') && (y == 'T')) {
			transitions++;
		} else {
			transversions++;
		}
	}
	double ratio = ((double)transitions) / transversions;
	fprintf(out, "%.3lf\n", ratio);

	free(first);
	free(second);
}
