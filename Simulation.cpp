#include "Simulation.h"

Simulation::Simulation() = default;

Simulation::Simulation(int consumers, int foodTypes) : 
	foodTypes_(foodTypes),
	consumers_(std::vector<Consumer>(consumers, Consumer(&warehouse_, foodTypes))),
	warehouse_(Warehouse(&supplier_)) {
	
}

void Simulation::process() {
	warehouse_.rot();
	TransferService::process();
	for (auto& it : consumers_) {
		it.process();
	}
}

Report Simulation::report() {
	Report report;
	return report;
}