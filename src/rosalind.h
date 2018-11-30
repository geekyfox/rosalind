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

/* 011-fibd.c */

void fibd_solve(FILE* in, FILE* out);

/* 012-grph.c */

void grph_solve(FILE* in, FILE* out);

/* 013-iev.c */

void iev_solve(FILE* in, FILE* out);

/* 014-lcsm.c */

void lcsm_solve(FILE* in, FILE* out);

/* 015-lia.c */

void lia_solve(FILE* in, FILE* out);

/* 016-mprt.c */

void mprt_solve(FILE* in, FILE* out);

/* 017-mrna.c */

int modulo_multiply(int x, int y);

void mrna_solve(FILE* in, FILE* out);

/* 018-orf.c */

struct strarr {
	int size;
	int alc;
	char** data;
	bool own_mem;
};

void strarr_init(struct strarr *arr, bool own_mem);
void strarr_add(struct strarr *arr, char *text);
void strarr_sort(struct strarr *arr);
void strarr_unique(struct strarr *set);
void strarr_free(struct strarr *arr);

char* fasta_read_payload_single(FILE* in);

void orf_solve(FILE* in, FILE* out);

/* 019-perm.c */

void intarr_swap(int* nums, int x, int y);
void intarr_print(FILE* out, const int* nums, size_t count);

bool perm_next(int* nums, int n);
void perm_solve(FILE* in, FILE* out);

/* 020-prtm.c */

struct aminoacid_mass {
    char aminoacid;
    double mass;
};
extern struct aminoacid_mass AMINOACID_MASSES[20];

double aminoacid_to_mass(char aminoacid);

void prtm_solve(FILE* in, FILE* out);

/* 021-revp.c */

void revp_solve(FILE* in, FILE* out);

/* 022-splc.c */

void splc_solve(FILE* in, FILE* out);

/* 023-lexf.c */

size_t alphabet_read(char* str, size_t size, FILE* in);
void alphabet_print_word(const int*, const char*, size_t, FILE* out);

void lexf_solve(FILE* in, FILE* out);

/* 024-lgis.c */

void lgis_solve(FILE* in, FILE* out);

/* 025-long.c */

void long_solve(FILE* in, FILE* out);

/* 026-pmch.c */

struct rna_bases_counts {
	int adenine;
	int cytosine;
	int guanine;
	int uracil;
};

void rna_increment_bases_count(struct rna_bases_counts* ptr, char nucleobase);
void rna_count_bases(struct rna_bases_counts*, const char* dna);

struct bigint {
	int* data;
	int  size;
	int  alc;
};

void bigint_normalize(struct bigint*);
struct bigint bigint_wrap(int x);
void bigint_free(struct bigint*);
void bigint_mult(struct bigint* ptr, int x);
void bigint_print(const struct bigint* ptr, FILE* out);

void pmch_solve(FILE* in, FILE* out);

#endif
