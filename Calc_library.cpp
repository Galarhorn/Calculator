#include <cstring>
#include <cstdlib>
#include "Calc library.h"

enum operation { PLUS, MUNUS, MULTIPLY, DIVID, NONE = -1 };
operation  getOperation(char c) {
	if (c == '+')
		return  PLUS;
	else if (c == '-')
		return  MUNUS;
	else if (c == '/')
		return  DIVID;
	else if (c == '*')
		return  MULTIPLY;
	return NONE;
}
bool parse(const char* expression, double& a, double& b, operation& c) {
	const char* space = strpbrk(expression, "+-*/");
	if (space == nullptr)
		return false;

	a = atof(expression);
	c = getOperation(*space);

	space++;
	b = atof(space);
	return true;
}
double minus(double a, double b) {
	return a - b;
}
double plus(double a, double b) {
	return a + b;
}
double multuply(double a, double b) {
	return a * b;
}
double devide(double a, double b) {
	return a / b;
}

double calculate(const char* expression) {
	double (*action[])(double, double) = {
		plus,minus,multuply,devide };
	double a;
	double b;
	operation c;

	bool parse_correct = parse(expression, a, b, c);
	if (!parse_correct)
		return 0;
	return action[c](a, b);


}