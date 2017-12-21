#include <dirent.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "rosalind.h"

typedef void (*solver_t)(FILE*, FILE*);

struct {
	const char* key;
	solver_t solver;
} SOLVERS[] = {
};

solver_t lookup_solver(const char* key)
{
	int count = sizeof(SOLVERS) / sizeof(SOLVERS[0]);
	for (int i=0; i<count; i++)
		if (strcmp(key, SOLVERS[i].key) == 0)
			return SOLVERS[i].solver;
	return NULL;
}

void invoke(const char* key, FILE* in, FILE* out)
{
	solver_t solver = lookup_solver(key);
	if (solver == NULL) {
		fprintf(stderr, "No solver for problem %s\n", key);
		return;
	}
	solver(in, out);
}

FILE* fopen_or_die(const char* filename, const char* mode)
{
	FILE* f = fopen(filename, mode);
	if (f == NULL) {
        	char* errmsg = strerror(errno);
		fprintf(stderr, "Can't open file %s : %s\n", filename, errmsg);
		exit(1);
	}
	return f;
}

void test_one_dataset(const char* puzzle_name, int dataset_id)
{
	const char* in_name_fmt = "testdata/rosalind_%s_%d_dataset.txt";
	const char* out_name_fmt = "testdata/rosalind_%s_%d_output.txt";
	const char* tmp_name_fmt = "temp/rosalind_%s_%d_output.txt";
	
	char in_name[256], out_name[256], tmp_name[256], diff_cmd[512];
	
	sprintf(in_name, in_name_fmt, puzzle_name, dataset_id);
	sprintf(out_name, out_name_fmt, puzzle_name, dataset_id);
	sprintf(tmp_name, tmp_name_fmt, puzzle_name, dataset_id);

	FILE* in = fopen_or_die(in_name, "r");
	FILE* out = fopen_or_die(tmp_name, "w");    
	invoke(puzzle_name, in, out);
	fclose(in);
	fclose(out);
    
	if (access(out_name, F_OK) == 0) {
		sprintf(diff_cmd, "diff -b %s %s", out_name, tmp_name);
		if (system(diff_cmd) != 0) {
			fprintf(stderr, "Test failed\n");
			exit(1);
		}
		unlink(out_name);
    	} else {
    		rename(tmp_name, out_name);
    	}
}

void test_suite(void)
{
	DIR* dir = opendir("testdata");
	struct dirent entry, *result;
	char puzzle[16], kind[16];
	int dataset_id;

	if (dir == NULL) {
		const char* fmt = "Can't open directory \"testdata\" : %s\n";
		char* errmsg = strerror(errno);
		fprintf(stderr, fmt, errmsg);
		exit(1);
	}
	while (true) {
		int retcode = readdir_r(dir, &entry, &result);
		if (retcode != 0) {
			perror("readdir_r()");
			exit(1);
		}
		if (result == NULL) break;
		const char* fmt = "rosalind_%[^_]_%d_%[^.].txt";
		if (sscanf(entry.d_name, fmt, puzzle, &dataset_id, kind) != 3)
			continue;
		if (strcmp(kind, "dataset") != 0)
			continue;
		test_one_dataset(puzzle, dataset_id);
	}
	closedir(dir);
}

int main(int argc, char** argv)
{
	if ((argc == 2) && (strcmp(argv[1], "test") == 0)) {
		test_suite();
		printf("All tests passed\n");
		return 0;
	}

	if (argc == 3) {
		FILE* in = fopen_or_die(argv[2], "r");
		invoke(argv[1], in, stdout);
		fclose(in);
		return 0;
	}

	printf("Usage: %s <problem name> <dataset file>\n", argv[0]);
}
