#include <assert.h>

#include "rosalind.h"

void tree_solve(FILE* in, FILE* out)
{
	int nodes = io_readint(in);
	io_skipline(in);

	int edges_needed = nodes - 1;
	char tmp[1024];
	while (io_readline(tmp, 1024, in, IO_ALLOW_EOF) > 0)
		edges_needed--;

	fprintf(out, "%d\n", edges_needed);
}

void io_skipline(FILE* in)
{
	char buffer[1024];
	int retcode = io_readline(buffer, 1024, in, 0);
	assert(retcode == 0);
}
