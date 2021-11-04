#define DEBUG

#include <iostream>
#include "Simulation.h"

int main() {
	Simulation simulation(3, 10, 100);
	for (auto& it : simulation.genReports(50)) {
		std::cout << it;

		// std::cout << it.*spot type*.*report type*[*food type(if needed)*];

		system("pause");
		system("cls");
	}
}