#include <assert.h>
#include <stdio.h>

#include "rosalind.h"

bool perm_next(int* nums, int n)
{
	int k = n - 2;
	while (nums[k] > nums[k+1]) {
		k--;
		if (k < 0)
			return false;
	}

	int l = n - 1;
	while (nums[l] < nums[k])
		l--;

	intarr_swap(nums, l, k);

	int i = k + 1;
	int j = n - 1;
	while (i < j)
		intarr_swap(nums, i++, j--);

	return true;
}

void perm_solve(FILE* in, FILE* out)
{
	int nums[7] = {1, 2, 3, 4, 5, 6, 7};
	int factorial = 1;
	int size = io_readint(in);

	for (int i=1; i<=size; i++)
		factorial *= i;
	fprintf(out, "%d\n", factorial);

	do
		intarr_print(out, nums, size);
	while (perm_next(nums, size));
}

void intarr_swap(int* nums, int x, int y)
{
	int t = nums[x];
	nums[x] = nums[y];
	nums[y] = t;
}

void intarr_print(FILE* out, const int* nums, size_t count)
{
	fprintf(out, "%d", nums[0]);
	for (int i=1; i<count; i++)
		fprintf(out, " %d", nums[i]);
	fprintf(out, "\n");
}
