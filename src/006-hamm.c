#include "rosalind.h"

void hamm_solve(FILE* in, FILE* out)
{
	char fst[1024], snd[1024];
	io_readline(fst, 1024, in, 0);
	io_readline(snd, 1024, in, 0);
	
	int result = hamm_distance(fst, snd);
	fprintf(out, "%d\n", result);
}

int hamm_distance(const char *x, const char *y)
{
	int result = 0;
	
	for(; *x; x++, y++)
		if (*x != *y)
			result++;

	return result;
}
