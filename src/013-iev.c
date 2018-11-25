#include <assert.h>

#include "rosalind.h"

void iev_solve(FILE* in, FILE* out)
{
	int dom_dom = io_readint(in);
	int dom_het = io_readint(in);
	int dom_rec = io_readint(in);
	int het_het = io_readint(in);
	int het_rec = io_readint(in);
	int rec_rec = io_readint(in);
	double result = dom_dom * 1.0 +
	                dom_het * 1.0 +
	                dom_rec * 1.0 +
	                het_het * 0.75 +
	                het_rec * 0.5 +
	                rec_rec * 0.0;
	fprintf(out, "%0.1lf\n", result * 2);
}
