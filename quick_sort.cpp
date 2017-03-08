#include <stdio.h>

void output_result(int a[], int len)
{
	int i;
	for (i = 0; i < len; i ++) {
		printf("%d\t", a[i]);
	}
	printf("\n");
}

int partition(int a[], int left, int right)
{
	int i, j;
	int r = a[right];
	int tmp;

	for (i = left, j = left - 1; i <= right - 1; i ++) {
		/* the Exquisite of partition */
		if (a[i] <= r) {
			j ++;
			//SWAP(a[i], a[j]);
			tmp = a[i];
			a[i] = a[j];
			a[j] = tmp;
		}
	}
	tmp = a[j + 1];
	a[j + 1] = a[right];
	a[right] = tmp;
	return j + 1;
}

void quick_sort(int a[], int left, int right)
{
	if (left < right) {
		int i = partition(a, left, right);
		output_result(a, 6);
		quick_sort(a, left, i - 1);
		quick_sort(a, i + 1, right);
	}
}

int main(int argc, char **argv)
{
	int a[] = { 12, 32, 1, 4, 6, 21 };

	printf("hello Quick-sort\n");
	quick_sort(a, 0, 5);
	output_result(a, 6);
	return 0;
}
