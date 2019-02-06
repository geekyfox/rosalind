#include <stdio.h>

#include "rosalind.h"

static bool sign_perm_next(int* nums, int count)
{
	for (int i=0; i<count; i++) {
		nums[i] *= -1;
		if (nums[i] < 0)
			return true;
	}
	return perm_next(nums, count);
}

void sign_solve(FILE* in, FILE* out)
{
	int nums[7] = {1, 2, 3, 4, 5, 6, 7};
	int factorial = 1;
	int size = io_readint(in);

	for (int i=1; i<=size; i++)
		factorial *= i * 2;
	fprintf(out, "%d\n", factorial);

	do
		intarr_print(out, nums, size);
	while (sign_perm_next(nums, size));
}
