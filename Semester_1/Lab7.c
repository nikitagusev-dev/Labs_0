#define _CRT_SECURE_NO_WARNINGS
#define SIZE_OF_STRING 2
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct operStack {
	char *array;
	int top;
	int sizeOfArray;
}operStack;

void operStackPush(operStack *stk, char symbol) {
	if (stk->top == stk->sizeOfArray - 1) {
		char *tempArray = (char *)calloc(stk->sizeOfArray * 2, sizeof(char));
		for (size_t i = 0; i < stk->sizeOfArray - 1; i++) {
			tempArray[i] = stk->array[i];
		}
		stk->array = tempArray;
		stk->sizeOfArray *= 2;
	}
	stk->array[stk->top] = symbol;
	stk->top++;
}

char operStackPop(operStack *stk) {
	if (stk->top == 0)
		return 0;
	else {
		char element = stk->array[stk->top - 1];
		stk->top--;
		if (stk->top < stk->sizeOfArray / 4) {
			char *tempArray = (char *)calloc(stk->sizeOfArray / 2, sizeof(char));
			for (size_t i = 0; i < (stk->sizeOfArray / 4) - 1; i++) {
				tempArray[i] = stk->array[i];
			}
			stk->array = tempArray;
			stk->sizeOfArray /= 2;
		}
		return element;
	}
}

typedef struct numberStack {
	int *array;
	int top;
	int sizeOfArray;
}numberStack;

void numberStackPush(numberStack *stk, int number) {
	if (stk->top == stk->sizeOfArray - 1) {
		int *tempArray = (int *)calloc(stk->sizeOfArray * 2, sizeof(int));
		for (size_t i = 0; i < stk->sizeOfArray - 1; i++) {
			tempArray[i] = stk->array[i];
		}
		stk->array = tempArray;
		stk->sizeOfArray *= 2;
	}
	stk->array[stk->top] = number;
	stk->top++;
}

int numberStackPop(numberStack *stk) {
	if (stk->top == 0)
		return 0;
	else {
		int element = stk->array[stk->top - 1];
		stk->top--;
		if (stk->top < stk->sizeOfArray / 4) {
			int *tempArray = (int *)calloc(stk->sizeOfArray / 2, sizeof(int));
			for (size_t i = 0; i < (stk->sizeOfArray / 4) - 1; i++) {
				tempArray[i] = stk->array[i];
			}
			stk->array = tempArray;
			stk->sizeOfArray /= 2;
		}
		return element;
	}
}

int checkValue(char symbol) {
	if (symbol >= '0' && symbol <= '9')
		return 1;
	if (symbol == '(')
		return 2;
	if (symbol == ')')
		return 3;
	if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/')
		return 4;
	return 0;
}

int priority(char symbol) {
	if (symbol == '(' || symbol == ')')
		return 1;
	if (symbol == '-' || symbol == '+')
		return 2;
	if (symbol == '*' || symbol == '/')
		return 3;
}

void calculateNumbers(numberStack *numStk, char operator) {
	if (numStk->top == 0 || numStk->top == 1) {
		printf("syntax error");
		exit(0);
	}
	int second = numberStackPop(numStk);
	int first = numberStackPop(numStk);
	int solution;
	switch (operator) {
	case '+':
		solution = first + second;
		break;
	case '-':
		solution = first - second;
		break;
	case '*':
		solution = first * second;
		break;
	case '/':
		if (second != 0) {
			solution = first / second;
			break;
		}
		else {
			printf("division by zero");
			exit(0);
		}
	}
	numberStackPush(numStk, solution);
}

void convertAndCalculate(numberStack *numStk, operStack *operStk, char *tempString, int *countOfIterations) {
	char current;
	int symbolsInBracket = 0;
	while ((current = fgetc(stdin)) != '\n') {
		(*countOfIterations)++;
		if (checkValue(current) == 1) {
			int tempIndex = 0;
			int currentNumber;
			tempString[tempIndex] = current;
			tempIndex++;
			int countOfTempBytes = SIZE_OF_STRING + 1;
			while (isdigit(current = fgetc(stdin)) != 0) {
				tempString = (char *)realloc(tempString, sizeof(char) * countOfTempBytes);
				tempString[tempIndex] = current;
				tempIndex++;
				countOfTempBytes++;
			}
			currentNumber = atoi(tempString);
			symbolsInBracket++;
			numberStackPush(numStk, currentNumber);
			memset(tempString, 0, tempIndex + SIZE_OF_STRING);
			if (current == '\n')
				break;
		}
		if (checkValue(current) == 2) {
			operStackPush(operStk, current);
			symbolsInBracket = 0;
		}
		else if (checkValue(current) == 3) {
			if (operStk->top == 0 || symbolsInBracket == 0) {
				printf("syntax error");
				exit(0);
			}
			else {
				while (checkValue(operStk->array[operStk->top - 1]) != 2) {
					calculateNumbers(numStk, operStackPop(operStk));
				}
				operStackPop(operStk);
			}
		}
		else if (checkValue(current) == 4) {
			while (operStk->top && ((priority(operStk->array[operStk->top - 1]) >= priority(current))))
				calculateNumbers(numStk, operStackPop(operStk));
			operStackPush(operStk, current);
		}
		else {
			printf("syntax error");
			exit(0);
		}
	}
	while (operStk->top)
		calculateNumbers(numStk, operStackPop(operStk));
}

void clear(numberStack *numStk, operStack *operStk, char *tempString) {
	free(numStk);
	free(operStk);
	free(tempString);
}

int main() {
	operStack *operStk;
	numberStack *numStk;
	char *tempString;
	int countOfIterations;

	operStk = (operStack *)calloc(1, sizeof(operStack));
	numStk = (numberStack *)calloc(1, sizeof(numberStack));
	tempString = (char *)calloc(SIZE_OF_STRING, sizeof(char));

	operStk->sizeOfArray = 1;
	numStk->sizeOfArray = 1;
	countOfIterations = 0;

	convertAndCalculate(numStk, operStk, tempString, &countOfIterations);
	if (countOfIterations > 0) {
		printf("%d", numberStackPop(numStk));
	}
	else {
		printf("syntax error");
		exit(0);
	}

	clear(numStk, operStk, tempString);

	return 0;
}
