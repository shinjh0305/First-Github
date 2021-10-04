#include <stdio.h>
#include <malloc.h>

enum type {
	lparen, add, sub, mul, div, rparen, etc
};

int in_op[] = { 20, 10, 10, 15, 15 };
int out_op[] = { 1, 10, 10, 15, 15 };

enum type gettype(int);
void print(int* stack, int* top);


int main() {
	int size = 5;
	int input;
	int input_test, stack_test;
	int* stack = (int*)malloc(sizeof(int)*size);
	int top = -1;
	enum type input_type;

	printf("Input? ");

	while (1) {
		input = getchar();
		if (input == '\n') {
			break;
		}

		input_type = gettype(input);

		switch (input_type) {

		case etc :
			printf("%d", input - '0');
			break;

		default :
			if (top == -1) {
				stack[++top] = input_type;
				break;
			}

			input_test = in_op[input_type];
			stack_test = out_op[stack[top]];

			if (input_test > stack_test) {
				if (size == top + 1) {
					size *= 2;
					stack = realloc(stack, sizeof(int)*size);
				}
				stack[++top] = input_type;
			}

			else {
				if (input_type == rparen) {
					while (stack[top] != lparen) {
						print(stack, &top);
					}
					top--;
					break;
				}

				else {
					while (top != -1 && out_op[stack[top]] >= input_test) {
						print(stack, &top);
					}
					stack[++top] = input_type;
				}
			}
			break;
		}
	}
	while (top != -1) {
		print(stack, &top);
	}
	printf("\n");
}

enum type gettype(int input) {
	switch (input) {
	case '(':
		return lparen; break;
	case '+':
		return add; break;
	case '-':
		return sub; break;
	case '*':
		return mul; break;
	case '/':
		return div; break;
	case ')':
		return rparen; break;
	default:
		return etc; break;
	}
}

void print(int* stack, int* top) {
	enum type op = stack[(*top)--];
	switch (op) {
	case 1:
		printf("+"); break;
	case 2:
		printf("-"); break;
	case 3:
		printf("*"); break;
	case 4:
		printf("/"); break;
	}
}