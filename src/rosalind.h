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

/* 004-fib.c */

int io_readint(FILE* in);

void fib_solve(FILE* in, FILE* out);

/* 005-gc.c */

struct fasta_pair {
	char* label;
	char* payload;
};

size_t fasta_read(struct fasta_pair* dst, size_t avail, size_t min, FILE* in);
size_t fasta_read_payload(char** dst, size_t avail, size_t min, FILE* in);
void fasta_free(struct fasta_pair*, size_t);

void gc_solve(FILE* in, FILE* out);

/* 006-hamm.c */

int hamm_distance(const char *x, const char *y);
void hamm_solve(FILE* in, FILE* out);

/* 007-iprb.c */

void iprb_solve(FILE* in, FILE* out);

/* 008-prot.c */

#include <stdbool.h>

extern char CODON_TABLE[64][5];

bool prot_translate(char* protein, const char* rna);
void prot_solve(FILE* in, FILE* out);

/* 009-subs.c */

int subs_search(const char* haystack, const char* needle);
void subs_solve(FILE* in, FILE* out);

/* 010-cons.c */

void cons_solve(FILE* in, FILE* out);

#endif
