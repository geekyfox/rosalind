#ifndef __ROSALIND_HEADER__
#define __ROSALIND_HEADER__

#include <stdbool.h>
#include <stdio.h>

/* build/invoke.c */

bool has_solver(const char* key);
void invoke(const char* key, FILE *in, FILE *out);

#endif