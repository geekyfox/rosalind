#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "rosalind.h"

static void read_uniprot(struct fasta_pair *item_ptr, const char* name)
{
	const char* url_base = "http://www.uniprot.org/uniprot";
	const char* cmd_fmt = "wget -nv %s/%s.fasta -O %s";

	char cmd[1024], fname[1024];

	sprintf(fname, "temp/%s.fasta", name);

	if (access(fname, F_OK) < 0) {
		sprintf(cmd, cmd_fmt, url_base, name, fname);
		int retcode = system(cmd);
		assert(retcode == 0);
	}

	FILE* fd = fopen(fname, "r");
	fasta_read(item_ptr, 1, 1, fd);
	fclose(fd);
}

static bool match(const char* prot, int offset)
{
	if (prot[offset] != 'N')
		return false;
	if (prot[offset+1] == 'P')
		return false;
	if ((prot[offset+2] != 'S') && (prot[offset+2] != 'T'))
		return false;
	if (prot[offset+3] == 'P')
		return false;
	return true;
}

void mprt_solve(FILE* in, FILE* out)
{
	struct fasta_pair item;
	char name[1024];

	while (io_readline(name, 1024, in, IO_ALLOW_EOF)) {
		read_uniprot(&item, name);
		char* prot = item.payload;
		bool flag = false;
		for (int i=0; prot[i+3]; i++) {
			if (! match(prot, i))
				continue;
			if (flag) {
				fprintf(out, " %d", i + 1);
			} else {
				fprintf(out, "%s\n%d", name, i + 1);
				flag = true;
			}
		}
		if (flag)
			fprintf(out, "\n");
		fasta_free(&item, 1);
	}
}
