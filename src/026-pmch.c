#include <stdlib.h>
#include <strings.h>

#include "rosalind.h"

void pmch_solve(FILE* in, FILE* out)
{
	char* dna = fasta_read_payload_single(in);

	struct rna_bases_counts stats;
	rna_count_bases(&stats, dna);

	struct bigint result = bigint_wrap(1);
	for (int i=stats.adenine; i>0; i--)
		bigint_mult(&result, i);
	for (int i=stats.cytosine; i>0; i--)
		bigint_mult(&result, i);
	bigint_print(&result, out);

	free(dna);
	bigint_free(&result);
}

void rna_count_bases(struct rna_bases_counts* ptr, const char* rna)
{
	bzero(ptr, sizeof(struct rna_bases_counts));
	for (int i=0; rna[i]; i++)
		rna_increment_bases_count(ptr, rna[i]);
}

void rna_increment_bases_count(struct rna_bases_counts* ptr, char nucleobase)
{
	switch (nucleobase) {
	case 'A':
		ptr->adenine++;
		break;
	case 'C':
		ptr->cytosine++;
		break;
	case 'G':
		ptr->guanine++;
		break;
	case 'U':
		ptr->uracil++;
		break;
	}
}

struct bigint bigint_wrap(int x)
{
	struct bigint num;
	num.data = calloc(4, sizeof(int));
	num.size = 1;
	num.alc = 4;
	num.data[0] = x;
	bigint_normalize(&num);
	return num;
}

void bigint_normalize(struct bigint *ptr)
{
	while (true) {
		for (int i=0; i<ptr->size-1; i++) {
			if (ptr->data[i] < 0) {
				int t = 1 - ptr->data[i] / 1000000;
				ptr->data[i] += t * 1000000;
				ptr->data[i+1] -= t;
			}
			ptr->data[i+1] += ptr->data[i] / 1000000;
			ptr->data[i] %= 1000000;
		}
		if (ptr->data[ptr->size-1] < 1000000)
			return;
		if (ptr->size == ptr->alc) {
			ptr->alc *= 2;
			size_t new_sz = sizeof(int) * ptr->alc;
			ptr->data = realloc(ptr->data, new_sz);
		}
		ptr->data[ptr->size] = 0;
		ptr->size++;
	}
}

void bigint_mult(struct bigint *ptr, int mult)
{
	for (int i=ptr->size-1; i>=0; i--)
		ptr->data[i] *= mult;
	bigint_normalize(ptr);
}

void bigint_print(const struct bigint *ptr, FILE* out)
{
	bool flag = false;
	for (int i=ptr->size-1; i>=0; i--) {
		if (flag) {
			fprintf(out, "%06d", ptr->data[i]);
			continue;
		}
		if (ptr->data[i] != 0) {
			fprintf(out, "%d", ptr->data[i]);
			flag = true;
		}
	}
	if (! flag)
		fprintf(out, "0");
}

void bigint_free(struct bigint *num)
{
	free(num->data);
}
