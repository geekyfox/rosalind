#include <assert.h>
#include <inttypes.h>
#include <stdint.h>

#include "rosalind.h"

void fibd_solve(FILE* in, FILE* out)
{
	uint64_t seq[128] = {0, 1}, births[128] = {0, 1};
	int months = io_readint(in);
	assert(months < 128);

	int lifetime = io_readint(in);

	for (int i=2; i<=months; i++) {
		births[i] = seq[i-1] - births[i-1];
		seq[i] = seq[i-1] + births[i];
		if (i >= lifetime)
			seq[i] -= births[i - lifetime];
	}
	fprintf(out, "%" PRIu64 "\n", seq[months]);
}
