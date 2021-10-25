#define DEBUG

#include <iostream>
#include "Simulation.h"

int main() {
	Simulation simulation(1, 10);
	for (int i = 0; true; ++i) {
		std::cout << "Iteration " << i + 1 << ": \n\r";
		simulation.process();
		std::cout << simulation.report();
		system("pause");
		system("cls");
	}
}