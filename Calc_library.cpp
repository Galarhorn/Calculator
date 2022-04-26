#include <cstring>
#include <cstdlib>
#include <cctype> // isdigit()
#include <iostream>
#include "Stack.h"
using std::cout;

enum class Operation { PLUS, MINUS, MULTIPLY, DIVIDE, NONE = -1};
enum class Priority { PLUS = 1, MINUS = 1, MULTIPLY = 2, DIVIDE = 2, NONE = 0};

Operation  getOperation(char c) {
	if (c == '+')
		return Operation::PLUS;
	else if (c == '-')
		return Operation::MINUS;
	else if (c == '*')
		return Operation::MULTIPLY;
	else if (c == '/')
		return Operation::DIVIDE;
	return Operation::NONE;
}

Priority getPriority(char c) {
	if (c == '+')
		return Priority::PLUS;
	else if (c == '-')
		return Priority::MINUS;
	else if (c == '*')
		return Priority::MULTIPLY;
	else if (c == '/')
		return Priority::DIVIDE;
	return Priority::NONE;
}

bool parse(const char* expression, double& a, double& b, Operation& c) {
	const char* oper = strpbrk(expression, "+-*/");
	if (oper == nullptr)
		return false;

	a = atof(expression);
	c = getOperation(*oper);

	oper++;
	b = atof(oper);
	return true;
}


double plus(double a, double b) {
	return a + b;
}

double minus(double a, double b) {
	return a - b;
}

double multiply(double a, double b) {
	return a * b;
}
double divide(double a, double b) {
	return a / b;
}

//Пока есть еще символы для чтения:
//Читаем очередной символ.
//Усли символ является числом, добавляем его к выходной строке.
//
//Если символ является бинарной операцией о1, тогда:
//1)
//... ИЛИ операции на вершине стека приоритетнее или такого же уровня приоретета как о1.
//... ИЛИ операция на вершине стека левоассоциативная с приорететом как у о1
//... выталкиваем верхний элемент стека в выходную строку:
//2) помещаем операцию о1 в стек.
//Когда входная строка закончилась, выталкиваем все символы из стека в выходную строку. В стеке должны были

void infix_to_postfix(const char* infix, char* postfix) {
	Stack<char, 100> stack;
	int j = 0;
	for (int i = 0; infix[i] != '\0'; i++) {
		char c = infix[i];
		if (isdigit(c) || isspace(c)) {
			postfix[j++] = c;
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/') {
			if (getPriority(top_element(stack)) >= getPriority(c)) {
				postfix[j++] = pop(stack);
			}
			push(stack, c);
		}
	}

	while (!is_empty(stack)) {
		postfix[j++]= pop(stack);
	}
	postfix[j] = '\0';
}

//Обработка входного символа :
//1. Если на вход подан операнд, он помещается на вершину стека.
//2. Если на вход подан знак операции, то соответствующая операция выполняется над требуемым количеством значений, извлечённых из стека, взятых в порядке добавления.Результат выполненной операции кладётся на вершину стека.
//3. Если входной набор символов обработан не полностью, перейти к шагу 1.
//После полной обработки входного набора символов результат вычисления выражения лежит на вершине стека.

double calculate_postfix(const char* postfix) {
	double (*action[])(double, double) = {
		plus,minus,multiply,divide
	};

	Stack<double, 100> numbers;

	for (int i = 0; postfix[i] != '\0'; i++) {
		char c = postfix[i];
		if (isdigit(c)) {
			double d = atof(&postfix[i]);
			push(numbers, d);
			// Добавить к i количество разрядов в числе d
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/') {
			double b = pop(numbers);
			double a = pop(numbers);
			Operation op = getOperation(c);
			double r = action[(int) op](a, b);
			push(numbers, r);
		}
	}

	return pop(numbers);
}

double calculate(const char* expression){	
	char* postfix = new char[strlen(expression) + 1];

	infix_to_postfix(expression, postfix);	
	double result = calculate_postfix(postfix);
	
	delete[] postfix;

	return result;
}