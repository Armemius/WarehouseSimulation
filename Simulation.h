#pragma once
#include "Supplier.h"
#include "Consumer.h"
#include "Warehouse.h"
#include <vector>

class Report {
public:
	Report(Warehouse warehouse, std::vector<Consumer> consumers);
	friend std::ostream& operator<<(std::ostream& out, const Report& rep);
private:
	Warehouse warehouse_;
	std::vector<Consumer> consumers_;
	std::list<Transmission> packages_;
};

class Simulation {
public:
	Simulation(int consumers, int foodTypes = 10);
	void process();
	Report report();

	friend int main();
private:
	Simulation();
	int foodTypes_ = 10;
	Warehouse warehouse_ = Warehouse(nullptr);
	Supplier supplier_;
	std::vector<Consumer> consumers_;
};