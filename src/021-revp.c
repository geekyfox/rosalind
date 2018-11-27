#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rosalind.h"

void revp_solve(FILE* in, FILE* out)
{
	char* dna = fasta_read_payload_single(in);
	int len = strlen(dna);

	for (int i=0; i<len; i++) {
		int sz = 0;
		for (int j=0; j<6; j++) {
			int p = i - j - 1;
			if (p < 0)
				break;
			int q = i + j;
			if (q >= len)
				break;
			if (dna[p] != revc_complement_base(dna[q]))
				break;
			sz++;
		}
		if (sz >= 2) {
			for (int j=sz; j>=2; j--) {
				int p = i - j + 1;
				int q = j * 2;
				fprintf(out, "%d %d\n", p, q);
			}
		}
	}
	free(dna);
}
