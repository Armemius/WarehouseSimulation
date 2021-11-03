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
#ifdef DEBUG
		std::cout << "COUNT - " << it.packs.size() <<" \n\r";
		std::cout << "TO - " << it.dest->name() << " \n\r";
#endif
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
	warehouse_(Warehouse(&supplier_)) {
	TransferService::packages_.clear();
	std::vector<Consumer> cons;
	for (int i = 0; i < consumers; ++i) {
		cons.push_back(Consumer(&warehouse_, foodTypes));
	}
	consumers_ = cons;
}

void Simulation::process() {
#ifdef DEBUG
	std::cout << "WAREHOUSE - ROT\n\r";
#endif
	warehouse_.rot();
#ifdef DEBUG
	std::cout << "TRANSFER SERVICE - PROCESS\n\r";
#endif
	TransferService::process();
#ifdef DEBUG
	std::cout << "CONSUMERS - PROCESS\n\r";
#endif
	for (auto& it : consumers_) {
		it.reloadWeights();
		it.process();
	}
#ifdef DEBUG
	std::cout << "WAREHOUSE - PROCESS\n\r";
#endif
	warehouse_.process();
#ifdef DEBUG
	std::cout << "SIMULATION PROCESS ITERATION COMPLETE\n\r";
#endif
}

Report Simulation::report() {
#ifdef DEBUG
	std::cout << "REPORT\n\r";
#endif
	Report report(warehouse_, consumers_);
#ifdef DEBUG
	std::cout << "REPORT COMPLETE\n\r";
#endif
	return report;
}