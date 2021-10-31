#define DEBUG

#include <iostream>
#include "Simulation.h"

int main() {
	Simulation simulation(3, 10);
	for (int i = 0; i < 50; ++i) {
		simulation.process();
		system("cls");
		std::cout << simulation.report();
		system("pause");
	}
}