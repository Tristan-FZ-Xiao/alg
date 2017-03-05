#include <stdio.h>

#define SWAP(a, b)	\
	do {		\
		a ^= b;	\
		b ^= a;	\
		a ^= b;	\
	} while (0);

void max_heap(int a[], int length, int cur)
{
	int left, right;
	int max = cur;

	left = 2 * cur;
	right = 2 * cur + 1;

	/* corner case */
	if (left > length) {
		return;
	}
	else if (right > length) {
		if (a[left - 1] > a[cur - 1]) {
			SWAP(a[left - 1], a[cur - 1]);
		}
		return;
	}

	if (a[left - 1] > a[max - 1])
		max = left;
	if (a[right - 1] > a[max - 1])
		max = right;
	if (max != cur) {
		SWAP(a[max - 1], a[cur - 1]);
		max_heap(a, length, max);
	}
}

void print_heap(int a[], int length)
{
	int i, j;
	int level = 0;

	for (i = 0, j = 0; i < length; i++, j++) {
		if (j > ((1 <<level) - 1)) {
			printf("\n");
			level ++;
			j = 0;
		}
		printf("%d ", a[i]);
	}
	printf("\n\n");
}

void build_max_heap(int a[], int length)
{
	int i;

	for (i = length / 2; i > 0; i --) {
		max_heap(a, length, i);
		print_heap(a, length);
	}
}

int get_max(int a[])
{
	return a[0];
}

void extract_max(int a[], int *length)
{
	a[0] = a[--*length];	
	max_heap(a, *length, 1);
}

void insert_key(int a[], int *length, int x)
{
	int parent = *length / 2;
	int cur = *length ++;
	a[cur - 1] = x;

	while (a[parent - 1] < a[cur - 1]) {
		SWAP(a[parent - 1], a[cur - 1]);
		cur = parent;
	}
}

void heap_sort(int a[], int length)
{
	int i;
	build_max_heap(a, length);
	print_heap(a, length);
	for (i = length; i > 1; i --) {
		SWAP(a[0], a[i - 1]);
		max_heap(a, i - 1, 1);
	}
}

int main(int argc, char **argv)
{
	int a[100] = {11, 2, 3, 4, 6, 100, 84, 23, 69, 71,123, 2, 4 ,6};

	//print_heap(a, sizeof(a)/sizeof(int));
	//build_max_heap(a, sizeof(a)/sizeof(int));
	heap_sort(a, 14);
	return 0;
}

