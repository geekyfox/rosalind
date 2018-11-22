#include <assert.h>
#include <stdlib.h>

#include "rosalind.h"

void prot_solve(FILE* in, FILE* out)
{
	char rna[10240], protein[10240];
	io_readline(rna, 10240, in, 0);
	bool flag = prot_translate(protein, rna);
	assert(flag);
	fprintf(out, "%s\n", protein);
}

char CODON_TABLE[64][5] = {
	"UUUF", "CUUL", "AUUI", "GUUV", "UUCF", "CUCL", "AUCI", "GUCV",
	"UUAL", "CUAL", "AUAI", "GUAV", "UUGL", "CUGL", "AUGM", "GUGV",
	"UCUS", "CCUP", "ACUT", "GCUA", "UCCS", "CCCP", "ACCT", "GCCA",
	"UCAS", "CCAP", "ACAT", "GCAA", "UCGS", "CCGP", "ACGT", "GCGA",
	"UAUY", "CAUH", "AAUN", "GAUD", "UACY", "CACH", "AACN", "GACD",
	"UAA!", "CAAQ", "AAAK", "GAAE", "UAG!", "CAGQ", "AAGK", "GAGE",
	"UGUC", "CGUR", "AGUS", "GGUG", "UGCC", "CGCR", "AGCS", "GGCG",
	"UGA!", "CGAR", "AGAR", "GGAG", "UGGW", "CGGR", "AGGR", "GGGG"
};

static char rna_to_aminoacid(const char* codon)
{
	if ((codon[0] == '\0') || (codon[1] == '\0') || (codon[2] == '\0'))
		return '\0';
	for (int i=0; i<64; i++) {
		if (CODON_TABLE[i][0] != codon[0])
			continue;
		if (CODON_TABLE[i][1] != codon[1])
			continue;
		if (CODON_TABLE[i][2] != codon[2])
			continue;
		return CODON_TABLE[i][3];
	}
	fprintf(stderr, "Bad RNA sequence: %c%c%c\n",
			codon[0], codon[1], codon[2]);
	exit(1);
}

bool prot_translate(char* protein, const char* rna)
{
	char aminoacid = rna_to_aminoacid(rna);
	if (aminoacid != 'M')
		return false;
	do {
		*(protein++) = aminoacid;
		rna += 3;
		aminoacid = rna_to_aminoacid(rna);
	} while ((aminoacid != '\0') && (aminoacid != '!'));
	if (aminoacid == '\0')
		return false;
	*protein = '\0';
	return true;
}
