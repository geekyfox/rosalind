#include <assert.h>
#include <stdio.h>

#include "rosalind.h"

void pper_solve(FILE* in, FILE* out)
{
	int n = io_readint(in);
	int k = io_readint(in);
	int result = 1;

	for (int i=0, j=n ; i<k ; i++, j--)
		result = modulo_multiply(result, j);

	fprintf(out, "%d\n", result);
}
