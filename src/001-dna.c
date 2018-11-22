#include <stdlib.h>
#include <strings.h>

#include "rosalind.h"

void dna_solve(FILE* in, FILE* out)
{
	char dna[1024];
	struct dna_bases_counts counts;
	
	io_readline(dna, 1024, in, 0);
	dna_count_bases(&counts, dna);

	fprintf(out, "%d ", counts.adenine);
	fprintf(out, "%d ", counts.cytosine);
	fprintf(out, "%d ", counts.guanine);
	fprintf(out, "%d\n", counts.thymine);
}

size_t io_readline(char* str, size_t size, FILE* stream, int flags)
{
	if (fgets(str, size, stream) != NULL) {
		return str_trim(str);
	} else if (feof(stream)) {
        if (flags & IO_ALLOW_EOF) {
            *str = '\0';
            return 0;
        }
		fprintf(stderr, "fgets(): Premature end of file\n");
	} else if (ferror(stream)) {
		perror("fgets()");
	} else {
		fprintf(stderr, "fgets(): Something went wrong\n");
	}
	exit(1);
}

size_t str_trim(char* str)
{
	size_t sz = strlen(str);
	while ((sz > 0) && (str[sz-1] == '\n'))
		str[--sz] = '\0';
	return sz;
}

void dna_count_bases(struct dna_bases_counts *result, const char *dna)
{
	bzero(result, sizeof(struct dna_bases_counts));
	for (int i=0; dna[i]; i++)
		dna_increment_bases_count(result, dna[i]);
}

void dna_increment_bases_count(struct dna_bases_counts* ptr, char nucleobase)
{
	switch (nucleobase) {
	case 'A':
		ptr->adenine++;
		break;
	case 'C':
		ptr->cytosine++;
		break;
	case 'G':
		ptr->guanine++;
		break;
	case 'T':
		ptr->thymine++;
		break;
	}
}
