#include <assert.h>
#include <inttypes.h>
#include <stdint.h>

#include "rosalind.h"

void fib_solve(FILE* in, FILE* out)
{
	uint64_t seq[64] = {0, 1};
	int months = io_readint(in);
	assert(months < 64);

	int pairs_per_litter = io_readint(in);

	for (int i=2; i<=months; i++)
		seq[i] = seq[i-2] * pairs_per_litter + seq[i-1];
	fprintf(out, "%" PRIu64 "\n", seq[months]);
}

int io_readint(FILE* in)
{
	int retcode, result;
	retcode = fscanf(in, "%d", &result);
	assert(retcode == 1);
	return result;
}
