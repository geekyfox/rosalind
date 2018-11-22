#include <assert.h>

#include "rosalind.h"

void iprb_solve(FILE* in, FILE* out)
{
	int dominant = io_readint(in);
	int hetero = io_readint(in);
	int recessive = io_readint(in);
	int total_organisms = dominant + hetero + recessive;
	int total_pairs = total_organisms * (total_organisms - 1);

	double weighted_suitable_pairs =
		dominant * (dominant - 1)   * 1.0 +
		dominant * hetero           * 1.0 +
		dominant * recessive        * 1.0 +
		hetero * dominant           * 1.0 +
		hetero * (hetero - 1)       * 0.75 +
		hetero * recessive          * 0.5 +
		recessive * dominant        * 1.0 +
		recessive * hetero          * 0.5 +
		recessive * (recessive - 1) * 0.0;

	double result = weighted_suitable_pairs / total_pairs;
	fprintf(out, "%0.5lf\n", result);
}
