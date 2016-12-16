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

char *get_num(char *input, int *num)
{
	int i = 0;
	*operand = 0;

	while (*(input + i) > '0' && *(input + i) < '9') {
		*operand += *operand * 10 + *(input + i);	
		i ++;
	}
	return (input + i);
}

/* get min() and max() */
char *get_bs(char *input int *num)
{
	int i = 0;
	int num_a, num_b;
	flag = 0;
	
	if (input == strstr(input, "min")) {
		flag = 1;
	}
	else if (input == strstr(input, "max")) {
		flag = 2;
	}

	input = get_num(input + 4, &num_a);
	/* jump space and , */
	while (*(input + i) < '0' || *(input + i) > '9') {
		i ++;
	}

	input = get_num(input + i, &num_b);

	if ((num_a > num_b && flag == 1) || (num_a < num_b && flag == 2)) {
		*num = num_b;
	}
	else if ((num_a < num_b && flag == 1) || (num_a > num_b && flag == 2)) {
		*num = num_a;
	}
	return input;
}

struct ops {
	int num;
	int type;
};

struct ops calulate_stack[1024] = {};
int stack_top;

enum OPS_TYPE {
	OPS_NUM = 1,
	OPS_OPERAND
};
int stack_push(int num, int type)
{
	if (stack_top < 1024) {
		calulate_stack[stack_top].num = num;
		calulate_stack[stack_top].type = type; 
		stack_top ++;
		return 0;
	}
	return -1;
}

int stack_pop(int *num, int *type)
{
	if (stack_top >= 0) {
		*num = calulate_stack[stack_top].num;
		*type = calulate_stack[stack_top].type;
		stack_top --;
		return 0;
	}
	return -1;
}

int str_to_calculate(char *ptr)
{
	int num  = 0;
	char op = 0;

	while (*ptr != 0) {
		if (*ptr > '0' && *ptr < '9') {
			ptr = get_num(ptr, &num);
		}
		else if (*ptr == 'm') {
			ptr = get_bs(ptr, &num);
		}
		else {
			switch (*ptr) {
			case '(':
			case ')':
				break;
			case '*'
			case '/'
				break;
			case '+'
			case '-'
			}
			if (*ptr == '(') {
				stack_push('(', OPS_OPERAND);
			}
			else if (*ptr)
			op = *ptr;
		}

		else if (*ptr == '(') {
			stack_push('(', OPS_OPERAND);

		}
		else if (*ptr == '*' || *ptr == '/') {
			op = *ptr; 
		}
	}
}

int main(int argc, char **argv)
{
	
}
