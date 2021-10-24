#pragma once
#include "Supplier.h"
#include "Consumer.h"
#include "Warehouse.h"
#include <vector>

class Report {

};

class Simulation {
public:
	Simulation(int consumers, int foodTypes = 10);
	void process();
	Report report();
private:
	Simulation();
	int foodTypes_ = 10;
	Warehouse warehouse_ = Warehouse(nullptr);
	Supplier supplier_;
	std::vector<Consumer> consumers_;
};