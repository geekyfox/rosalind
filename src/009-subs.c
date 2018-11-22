#include <stdbool.h>

#include "rosalind.h"

int subs_search(const char* haystack, const char* needle)
{
	int offset = 0, scan = 0;
	while (true) {
		char n = needle[scan], h = haystack[scan + offset];
		if (n == '\0')
			return offset;
		if (h == '\0')
			return -1;
		if (n != h) {
			offset++;
			scan = 0;
			continue;
		}
		scan++;
	}
}

void subs_solve(FILE* in, FILE* out)
{
	char haystack[1024], needle[1024];
	
	io_readline(haystack, 1024, in, 0);
	io_readline(needle, 1024, in, 0);

	int offset=0;
	while (true) {
		int delta = subs_search(haystack + offset, needle);
		if (delta < 0)
			break;
		offset += delta + 1;
		fprintf(out, "%d ", offset);
	}
	fprintf(out, "\n");
}
