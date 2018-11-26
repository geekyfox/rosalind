#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "rosalind.h"

struct aminoacid_mass
AMINOACID_MASSES[] = {
	{'A', 71.03711,},
	{'C', 103.00919,},
	{'D', 115.02694,},
	{'E', 129.04259,},
	{'F', 147.06841,},
	{'G', 57.02146,},
	{'H', 137.05891,},
	{'I', 113.08406,},
	{'K', 128.09496,},
	{'L', 113.08406,},
	{'M', 131.04049,},
	{'N', 114.04293,},
	{'P', 97.05276,},
	{'Q', 128.05858,},
	{'R', 156.10111,},
	{'S', 87.03203,},
	{'T', 101.04768,},
	{'V', 99.06841,},
	{'W', 186.07931,},
	{'Y', 163.06333,},
};

double aminoacid_to_mass(char aminoacid)
{
    int ct = sizeof(AMINOACID_MASSES) / sizeof(AMINOACID_MASSES[0]);
    for (int i=ct-1; i>=0; i--)
        if (AMINOACID_MASSES[i].aminoacid == aminoacid)
            return AMINOACID_MASSES[i].mass;
    fprintf(stderr, "Unknown aminoacid in aminoacid_to_mass(): %c\n", aminoacid);
    exit(1);
}

static double protein_to_mass(char* protein)
{
	double result = 0;
	for (; *protein; protein++)
        result += aminoacid_to_mass(*protein);
	return result;
}

void prtm_solve(FILE* in, FILE* out)
{
	char protein[1024];
    io_readline(protein, 1024, in, 0);
	double mass = protein_to_mass(protein);
	fprintf(out, "%.3lf\n", mass);
}
