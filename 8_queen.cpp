#include <stdio.h>
#include <stdlib.h>

int conflict_judge(int *a, int len, int val)
{
	int i, j;
	int delta = 0;
	int flag = 0;

	for (i = 0; i < len; i ++) {
		/* 列 */
		if (a[i] == val) {
			return 0;
		}
		/* 对角 */
		delta = len - i;
		if (val == a[i] + delta) {
			return 0;
		}
		/* 反对角 */
		if (val == a[i] - delta) {
			return 0;
		}
	}
	return 1;
}
static int num = 1;
void output_result(int *a, int len)
{
	int i;

	printf("%d-Queen-issue-result(%d)\n", len, num ++);
	for (i = 0; i < len; i++) {
		printf("%d\t", a[i]);
	}
	printf("\n");
}

void queens(int *a, int len, int cur)
{
	int i;

	for (i = 0; i < len; i ++) {
		if (conflict_judge(a, cur, i)) {
			a[cur] = i;
			if (len == cur + 1) {
				output_result(a, len);
				//exit(0);
			}
			queens(a, len, cur + 1);
		}
	}
	return;
}

int main(int argc, char **argv)
{
	int a[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
	//int a[4] = {-1, -1, -1, -1};

	queens(a, 8, 0);
	return 0;
}