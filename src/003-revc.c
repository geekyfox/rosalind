#include <stdlib.h>
#include <string.h>

#include "rosalind.h"

void revc_solve(FILE* in, FILE* out)
{
	char dna[1024];
	io_readline(dna, 1024, in, 0);
	revc_apply(dna);
	fprintf(out, "%s\n", dna);
}

char* revc_apply(char* dna)
{
	revc_reverse(dna);
	revc_complement(dna);
	return dna;
}

void revc_reverse(char* ptr)
{
	char* last = ptr + strlen(ptr) - 1;
	while (ptr < last) {
		char t = *ptr;
		*(ptr++) = *last;
		*(last--) = t;
	}
}

void revc_complement(char* dna)
{
	for( ; *dna ; dna++)
		*dna = revc_complement_base(*dna);
}

char revc_complement_base(char nucleobase)
{
	switch(nucleobase)
	{
	case 'A':
		return 'T';
	case 'C':
		return 'G';
	case 'G':
		return 'C';
	case 'T':
		return 'A';
	default:
		return '?';	
	}
}
