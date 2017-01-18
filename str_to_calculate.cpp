#include <stdio.h>

/*	给出类似字符串： 1+2*3-4*min(3,5)*max(6,8)，保证一定正确，
 *	请进行解析并算出正确结果。
 *	运算符优先级：
 *	1. （）
 *	2. * /
 *	3. + -
 *	运算操作数：
 *	1. 数字
 *	2. min()
 *	3. max()
 */

 /*	The solution: use stack as the oprand sharper.
  *	input: 1 + 2 * 3 - 4
  *	1) output: 1
  *	2) stack_push(+)
  *	3) output: 1 2
  *	4) stack_push(*): + *
  *	5) output 1 2 3
  *	6) compare: * -, pop(*), output 1 2 3 * => 1 6, stack_push(-): + -
  *	7) pop(-): output: 1 6 4 - => 1 2
  *	8) pop(+): output: 1 2 + => 3
  */
#define MAX_TOP		128
static int top = 0;
static int base = 0;
static char stack[MAX_TOP] = {0};

int stack_push(char ops)
{
	if (MAX_TOP < top) {
		return -1;
	}

	stack[top ++] = ops;
	return 0;
}

int stack_pop(char *ops)
{
	if (top < 0) {
		return -1;
	}
	
	*ops = stack[--top];
	stack[top] = '\0';
	return 0;
}

#include <string.h>
#include <stdlib.h>

int sharp_string(char *input)
{
	int len = 0;
	char *output = NULL;
	int i = 0;

	if (input) {
		len = strlen(input);
		output = (char *)malloc(len * sizeof(char*));
		memset(output, 0, len);

		for (; i < len; i ++) {
			char c = *(input + i);

			if (c > '0' && c < '9') {
				*(output + i) = *(input + i);
			}
			else if (c == 'm') {
			}
			else {
			}
		}
		return 0;
	}	
	return -1;
}

int main(int argc, char **argv)
{
	int i = 0;

	stack_push('t');
	stack_push('r');
	stack_push('i');
	stack_push('s');
	stack_push('t');
	stack_push('a');
	stack_push('n');

	for (; i < MAX_TOP; i ++) {
		char c = '\0';

		if (stack_pop(&c) != 0) {
			break;
		}
		printf("%c", c);
	}

	return 0;
}
