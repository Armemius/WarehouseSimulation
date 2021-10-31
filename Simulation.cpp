#include "Simulation.h"
#include "Storage.h"
#include <unordered_map>

// Report
Report::Report(Warehouse warehouse, std::vector<Consumer> consumers) : 
	warehouse_(warehouse),
	consumers_(consumers),
	packages_(TransferService::packages_) {}

std::ostream& operator<<(std::ostream& out, const Report& rep) {
	out << "**[WAREHOUSE]**\n\r";
	out << "Money: " << rep.warehouse_.cash_ << "\n\r";
	for (auto& it : rep.warehouse_.storages_) {
		out << "Storage(" << it.first << "):" << it.second.prodCount() << "\n\r";
	}
	for (auto& it : rep.warehouse_.demand_) {
		out << "Demand(" << it.first << "):" << it.second << "\n\r";
	}
	for (auto& it : rep.warehouse_.dayDemand_) {
		out << "Daily demand(" << it.first << "):" << it.second << "\n\r";
	}
	out << "\n\r**[CONSUMERS]**\n\r";
	int cnt = 1;
	for (auto& it : rep.consumers_) {
		out << "[Consumer " << cnt << "]\n\r";
		for (auto& jt : it.weights_) {
			out << "Weight(" << jt.first << "):" << jt.second << "\n\r";
		}
		auto vrt = it.virtualProducts_.begin();
		for (auto& jt : it.products_) {
			const std::string sus = jt.first;
			out << "Stored(" << jt.first << "):" << jt.second << " + " << it.virtualProducts_.at(jt.first) << " = " << jt.second + it.virtualProducts_.at(jt.first) << "\n\r";
		}

		out << "\n\r";
		cnt++;
	}
	out << "\n\r**[Transfer]**\n\r";
	for (auto& it : rep.packages_) {
		std::string name = it.dest->name();
		out << "(" << it.packs[0].name() << " x" << it.packs.size() << "; to: " << name << "; in:" << it.time << ")\n\r";
	}
	return out;
}

// Simulation
Simulation::Simulation() {
	TransferService::packages_.clear();
}

Simulation::Simulation(int consumers, int foodTypes) : 
	foodTypes_(foodTypes),
	consumers_(std::vector<Consumer>(consumers, Consumer(&warehouse_, foodTypes))),
	warehouse_(Warehouse(&supplier_)) {
	TransferService::packages_.clear();
}

void Simulation::process() {
	warehouse_.rot();
	TransferService::process();
	for (auto& it : consumers_) {
		it.reloadWeights();
		it.process();
	}
	warehouse_.process();
}

Report Simulation::report() {
	Report report(warehouse_, consumers_);
	return report;
}