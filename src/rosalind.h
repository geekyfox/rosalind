#ifndef __ROSALIND_HEADER__
#define __ROSALIND_HEADER__

#include <stdbool.h>
#include <stdio.h>

/* build/invoke.c */

bool has_solver(const char* key);
void invoke(const char* key, FILE *in, FILE *out);

/* 001-dna.c */

#define IO_ALLOW_EOF 1

size_t io_readline(char* str, size_t size, FILE* stream, int flags);
size_t str_trim(char* str);

struct dna_bases_counts {
	int adenine;
	int cytosine;
	int guanine;
	int thymine;
};

void dna_increment_bases_count(struct dna_bases_counts*, char nucleobase);
void dna_count_bases(struct dna_bases_counts*, const char* dna);
void dna_solve(FILE *in, FILE *out);

/* 002-rna.c */

void rna_transcribe(char* rna, const char* dna);
void rna_solve(FILE* in, FILE* out);

/* 003-revc.c */

char* revc_apply(char* dna);
void revc_reverse(char* ptr);
void revc_complement(char* dna);
char revc_complement_base(char nucleobase);
void revc_solve(FILE* in, FILE* out);

#endif
