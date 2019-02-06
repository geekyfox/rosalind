#include <stdlib.h>
#include "rosalind.h"

void sseq_solve(FILE* in, FILE* out)
{
	char *super, *sub;
	fasta_read_payload_pair(&super, &sub, in);

	int i = 0, j = 0;

	while (sub[j]) {
		if (super[i] == sub[j]) {
			fprintf(out, "%d ", i + 1);
			j++;
		}
		i++;
	}
	fprintf(out, "\n");

	free(super);
	free(sub);
}

void fasta_read_payload_pair(char** first, char** second, FILE* in)
{
	char* lines[2];
	fasta_read_payload(lines, 2, 2, in);
	*first = lines[0];
	*second = lines[1];
}
