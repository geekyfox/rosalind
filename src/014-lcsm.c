#include <stdlib.h>
#include <string.h>

#include "rosalind.h"

static size_t max_prefix_len(const char* haystack, const char* prefix)
{
	size_t scan = 0, offset = 0, max_scan = 0;
	while (prefix[scan] && haystack[scan + offset]) {
		if (prefix[scan] == haystack[scan + offset]) {
			scan++;
			if (scan > max_scan)
				max_scan = scan;
		} else {
			scan = 0;
			offset++;
		}
	}
	return max_scan;
}

void lcsm_solve(FILE* in, FILE* out)
{
	char best[1024] = {'\0'}, seq[1024];
	size_t best_len = 0, seq_len;

	char* dnas[1000];
	size_t count = fasta_read_payload(dnas, 1000, 1, in);

	for (int i=0; dnas[0][i]; i++) {
		strcpy(seq, dnas[0] + i);
		for (int j=1; j<count; j++) {
			seq_len = max_prefix_len(dnas[j], seq);
			seq[seq_len] = '\0';
			if (seq_len < best_len)
				break;
		}
		if (seq_len < best_len)
			continue;
		if ((seq_len == best_len) && (strcmp(seq, best) <= 0))
			continue;
		strcpy(best, seq);
		best_len = seq_len;
	}
	fprintf(out, "%s\n", best);
	for (int i=0; i<count; i++)
		free(dnas[i]);
}
