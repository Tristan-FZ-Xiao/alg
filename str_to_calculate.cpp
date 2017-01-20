#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
 /*     Example:
  *	The solution: use stack as the oprand sharper.
  *	input: 1 + 2 * 3 - (4 + min(3, 5)) * 5
  *	1) output: 1
  *	2) compare NULL +, stack_push(+)
  *	3) output: 1 2
  *	4) compare + *, stack_push(*)
  *	5) output 1 2 3
  *	6) compare: * -, pop(*), output 1 2 3 * => 1 6
  *	7) compare: + -, pop(+), output 1 6 + => 7
  *	8) compare NULL -, stack_push(-)
  *	9) compare -, (, satck_push((): - (
  *	10) output 7 4
  *	11) compare ( +, stack_push(+): - ( +
  *	12) found m => get min or max: 3 => output 7 4 3
  *     13) compare ) + => stack_pop(+), output 7 4 3 + => 7 7
  *     14) compare ) ( => match up, clean
  *     15) compare - * => stack_push(*) - *
  *     16) output 7 7 5
  *     17) match end: stack_pop(*) => 7 7 * 5 => 7 35
  *     18) stack_pop(-) => 7 - 35 => -28
  */
#define MAX_TOP		128
#define MAX_OUTPUT_LEN  128
static int top = 0;
static int base = 0;
static char stack[MAX_TOP] = {0};
static int output[MAX_OUTPUT_LEN] = {0};
static char opt_priority[128] = {0};

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

int is_stack_empty(void)
{
	return top == 0 ? 1 : 0;
}

static int get_num(char *input, int *num)
{
        int i = 0;
        *num = 0;
        
        while (*(input + i) >= '0' && *(input + i) <= '9') {
                *num = *num * 10 + *(input + i) - '0';
                i ++;
        }
        return i;
}

void init_opt_priority(void)
{
	opt_priority['+'] = 1;
	opt_priority['-'] = 1;
	opt_priority['*'] = 2;
	opt_priority['/'] = 2;
	opt_priority['('] = 3;
	opt_priority[')'] = 1;
}

inline int get_opt_priority(char c)
{
	if (c >= 0 && c < 128)
		return opt_priority[c];
	else
		return -1;
}

static int get_m_x(char *input, int *num)
{
	int i = 4;
	int j = 0;
	int max_flag = 0;
	int a[2];

	if (!strncmp(input, "max", 3))
		max_flag = 1;

	while (*(input + i) != ')') {
		if (*(input + i) > '0' && *(input + i) < '9') {
			i += get_num(input + i, &a[j ++]);
		}
		else {
			i ++;
		}
	}
	*num = (max_flag == 1 ? (a[0] > a[1] ? a[0] : a[1]) : (a[0] < a[1] ? a[0] : a[1]));
	return i ++;
}

int calculate_a_b(char opt, int a, int b)
{
	
	switch (opt) {
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		return a / b;
	default:
		return -1;
	}
}

int calculate_string(char *input)
{
	char c = 0;
	int i = 0;
	int j = 0;

	if (input) {
 		while (*(input + i) != '\0') {
			c = *(input + i);
			if (c == ' ') {
				i ++;
			} else if (c >= '0' && c <= '9') {
				i += get_num(input + i, &output[j++]);
			} else if (c == 'm') {
				i += get_m_x(input + i, &output[j++]);
			} else {
				if (is_stack_empty()) {
					stack_push(c);
				}
				else {
					char prev_opt = 0;

					stack_pop(&prev_opt);
					if (get_opt_priority(prev_opt) >= get_opt_priority(c)) {
						int ret = calculate_a_b(prev_opt, output[j - 2], output[j - 1]);

						if (ret == -1) {
							stack_push(prev_opt);
						}
						else {
							output[j - 2] = ret;
							j --;
						}
						stack_push(c);
					}
					else {
						stack_push(prev_opt);
						stack_push(c);
					}
				}
				i ++;
			}
		}

		while (!is_stack_empty()) {
			char opt = 0;
			int ret = 0;

			stack_pop(&opt);
			ret = calculate_a_b(opt, output[j - 2], output[j - 1]);
			if (ret != -1) {
				output[j - 2] = ret;
				j --;	
			}
		}
		return output[0];
	}	
	return -1;
}

int main(int argc, char **argv)
{
	int i = 0;
	init_opt_priority();
	printf("Calculate output:\t%d\n", calculate_string("3*((12+max(3, 6)) / (4 - 1))"));
	return 0;
}
