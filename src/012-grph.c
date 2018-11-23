#include <stdbool.h>
#include <string.h>

#include "rosalind.h"

static bool match(const char *x, const char *y)
{
	for (int i=0; i<3; i++)
		if (x[i] != y[i])
			return false;
	return true;
}

void grph_solve(FILE* in, FILE* out)
{
	struct fasta_pair data[500];
	int item_ct = fasta_read(data, 500, 0, in);
	for (int i=0; i<item_ct; i++) {
		int sz = strlen(data[i].payload);
		char* suffix = data[i].payload + (sz - 3);
		for (int j=0; j<item_ct; j++) {
			if (i == j)
				continue;
			if (! match(suffix, data[j].payload))
				continue;
			fprintf(out, "%s %s\n", data[i].label, data[j].label);
		}
	}
	fasta_free(data, item_ct);
}
