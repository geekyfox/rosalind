#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rosalind.h"

static void collect(struct strarr* accum, const char* dna)
{
	char rna[1024], protein[1024];
	rna_transcribe(rna, dna);

	for (char* ptr=rna; *ptr; ptr++)
		if (prot_translate(protein, ptr))
			strarr_add(accum, protein);
}

void orf_solve(FILE* in, FILE* out)
{
	char* dna = fasta_read_payload_single(in);

	struct strarr result;
	strarr_init(&result, true);

	collect(&result, dna);
	collect(&result, revc_apply(dna));
	strarr_unique(&result);

	for (int i=0; i<result.size; i++)
		fprintf(out, "%s\n", result.data[i]);

	strarr_free(&result);
	free(dna);
}

char* fasta_read_payload_single(FILE* in)
{
	char* result;
	fasta_read_payload(&result, 1, 1, in);
	return result;
}

void strarr_init(struct strarr *arr, bool own_mem)
{
	bzero(arr, sizeof(struct strarr));
	arr->own_mem = own_mem;
}

void strarr_add(struct strarr *arr, char* text)
{
	if (arr->size == arr->alc) {
		int q = arr->size < 8 ? 8 : arr->size * 2;
		arr->alc = q;
		arr->data = realloc(arr->data, q * sizeof(char*));
	}
	if (arr->own_mem)
		text = strdup(text);
	arr->data[arr->size++] = text;
}

void strarr_free(struct strarr *arr)
{
	if (arr->own_mem)
		for (int i=arr->size-1; i>=0; i--)
			free(arr->data[i]);
	free(arr->data);
	strarr_init(arr, arr->own_mem);
}

void strarr_unique(struct strarr *set)
{
	if (set->size == 0)
		return;
	strarr_sort(set);
	int p = 0;
	for (int q=1; q<set->size; q++) {
		if (strcmp(set->data[p], set->data[q]) == 0) {
			if (set->own_mem)
				free(set->data[q]);
		} else {
			set->data[++p] = set->data[q];
		}
	}
	set->size = p + 1;
}

static int strcmp_wrapper(const void* x, const void* y)
{
	const char* a = *(const char**)x;
	const char* b = *(const char**)y;
	return strcmp(a, b);
}

void strarr_sort(struct strarr *arr)
{
	qsort(arr->data, arr->size, sizeof(char*), strcmp_wrapper);
}
