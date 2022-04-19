#include <iostream>
#include <cstring>
#include "Calc_library.h"
using std::cout;
using std::cin;

void run() {
	cout << "Enter 'exit' ti quit.\n";
	char buffer[500];
	while (true) {
		cout << "Enter expression: ";
		std::cin.getline(buffer, sizeof(buffer));
		if (strncmp("exit", buffer, 4) == 0)
			break;
		cout << "Result: " << calculate(buffer) << std::endl;

	}
}

int main()
{
	run();
}