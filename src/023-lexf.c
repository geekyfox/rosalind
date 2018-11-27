#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "rosalind.h"

static bool next(int* indices, int alphabet_size, int word_len)
{
	int i = word_len - 1;
	indices[i]++;

	while ((i > 0) && (indices[i] == alphabet_size)) {
		indices[i] = 0;
		i--;
		indices[i]++;
	}

	return (indices[0] < alphabet_size);
}

void lexf_solve(FILE* in, FILE* out)
{
	char alphabet[16];
	size_t alphabet_size = alphabet_read(alphabet, 16, in);

	int word_len = io_readint(in);

	int indices[16];
	bzero(indices, sizeof(indices));

	do
		alphabet_print_word(indices, alphabet, word_len, out);
	while (next(indices, alphabet_size, word_len));
}

size_t alphabet_read(char* str, size_t size, FILE* in)
{
	char line[size * 2];
	int line_length = io_readline(line, size*2, in, 0);
	int alphabet_size = line_length / 2 + 1;
	for (int i=0; i<alphabet_size; i++)
		str[i] = line[i * 2];
	return alphabet_size;
}

void alphabet_print_word(const int* indices, const char* alphabet,
                         size_t word_len, FILE* out)
{
	for (int i=0; i<word_len; i++)
		fputc(alphabet[indices[i]], out);
	fputc('\n', out);
}