#include <assert.h>

#include "rosalind.h"

void lia_solve(FILE* in, FILE* out)
{
	double probability[130][130];

	int generation = io_readint(in);
	int at_least = io_readint(in);
	int total = 1 << generation;

	for (int i=0; i<130; i++)
		for (int j=0; j<130; j++)
			probability[i][j] = 0.0;

	probability[0][0] = 1.0;

	for(int out_of=1; out_of<=total; out_of++) {
		probability[0][out_of] = 1.0;
		for (int belong=1; belong<=at_least; belong++) {
			probability[belong][out_of] =
				probability[belong-1][out_of-1] * 0.25 +
				probability[belong][out_of-1] * 0.75;
		}
	}
	fprintf(out, "%.3lf\n", probability[at_least][total]);
}
