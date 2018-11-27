#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "rosalind.h"

static bool increase(int fst, int snd)
{
	return fst < snd;
}

static bool decrease(int fst, int snd)
{
	return snd < fst;
}

static int seek(int* dst, const int* numbers, size_t sz,
                bool (*right_order)(int, int))
{
	/* index -> index of previous number in sequence */
	int predecessor_index[sz];
	/* length of sequence -> index of last item in sequence */
	int seq_terminal_index[sz];
	/* length of longest found sequence */
	int max_seqlen = 0;

	for (int i=0; i<sz; i++) {
		int num = numbers[i];
		int prefix_len = 0;

		for (int j=max_seqlen-1; j>=0; j--) {
			int terminal = numbers[seq_terminal_index[j]];
			if (right_order(terminal, num)) {
				prefix_len = j + 1;
				predecessor_index[i] = seq_terminal_index[j];
				break;
			}
		}
		if (prefix_len == max_seqlen) {
			seq_terminal_index[max_seqlen++] = i;
			continue;
		}

		int terminal = numbers[seq_terminal_index[prefix_len]];
		if (right_order(num, terminal)) {
			seq_terminal_index[prefix_len] = i;
		}
	}

	int i = seq_terminal_index[max_seqlen - 1];
	for (int j=max_seqlen - 1; j>=0; j--) {
		dst[j] = numbers[i];
		i = predecessor_index[i];
	}
	return max_seqlen;
}

void lgis_solve(FILE* in, FILE* out)
{
	int retcode, size, subsize;
	int numbers[10240], result[10240];

	retcode = fscanf(in, "%d", &size);
	assert(retcode == 1);

	for (int i=0; i<size; i++) {
		retcode = fscanf(in, "%d", &numbers[i]);
		assert(retcode == 1);
	}

	subsize = seek(result, numbers, size, increase);
	intarr_print(out, result, subsize);

	subsize = seek(result, numbers, size, decrease);
	intarr_print(out, result, subsize);
}
