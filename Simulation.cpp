#include "Simulation.h"
#include "Storage.h"
#include <unordered_map>

// Report
DayReport::DayReport(Warehouse warehouse, std::vector<Consumer> consumers, int foodTypes, int consums) :
	warehouse_(warehouse),
	consumers_(consumers),
	packages_(TransferService::packages_),
	foodTypes(foodTypes) {
	for (int i = 0; i < consums; ++i) {
		this->consumersReport.push_back(ConsumerReport_());
	}
	for (int i = 0; i < foodTypes; ++i) {
		this->warehouseReport.get.insert({ Product::names[i], 0 });
		this->warehouseReport.defects.insert({ Product::names[i], 0 });
		this->warehouseReport.rotten.insert({ Product::names[i], 0 });
		this->warehouseReport.products.insert({ Product::names[i], 0 });
		this->warehouseReport.packages.insert({ Product::names[i], 0 });
		this->warehouseReport.demand.insert({ Product::names[i], 0 });
		this->warehouseReport.sended.insert({ Product::names[i], 0 });
		this->warehouseReport.requested.insert({ Product::names[i], 0 });
		for (auto& it : consumersReport) {
			it.requested.insert({ Product::names[i], 0 });
			it.sended.insert({ Product::names[i], 0 });
		}
	}
}

std::ostream& operator<<(std::ostream& out, const DayReport& rep) {
	out << "**[WAREHOUSE]**\n\r";
	out << "Money: " << rep.warehouse_.cash_ << "\n\r";
	for (auto& it : rep.warehouse_.storages_) {
		out << "Storage(" << it.first << "):" << it.second.prodCount() << " [" << it.second.cargo_ << " + " << it.second.virtualCargo_ << " of "<< it.second.maxCargo_ << "]\n\r";
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
		if (it.dest == nullptr) {
			out << "(" << it.packs[0].name() << " x" << it.packs.size() << "; to: " << "junkyard" << "; in:" << it.time << ")\n\r";
			continue;
		}
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

Simulation::Simulation(int consumers, int foodTypes, int warehouseCapacity) : 
	foodTypes_(foodTypes),
	warehouse_(Warehouse(&supplier_, warehouseCapacity, foodTypes)) {
	TransferService::packages_.clear();
	std::vector<Consumer> cons;
	for (int i = 0; i < consumers; ++i) {
		cons.push_back(Consumer(&warehouse_, foodTypes));
	}
	consumers_ = cons;
}

DayReport Simulation::process() {
	DayReport report(warehouse_, consumers_, foodTypes_, consumers_.size());
	int startCash = warehouse_.cash_;
#ifdef DEBUG
	std::cout << "WAREHOUSE - ROT\n\r";
#endif
	warehouse_.rot(report);
#ifdef DEBUG
	std::cout << "TRANSFER SERVICE - PROCESS\n\r";
#endif
	TransferService::process(report);
#ifdef DEBUG
	std::cout << "CONSUMERS - PROCESS\n\r";
#endif
	int index = 0;
	for (auto& it : consumers_) {
		it.reloadWeights();
		it.process(&report, index++);
	}
#ifdef DEBUG
	std::cout << "WAREHOUSE - PROCESS\n\r";
#endif
	warehouse_.process(report);
#ifdef DEBUG
	std::cout << "SIMULATION PROCESS ITERATION COMPLETE\n\r";
#endif
	for (auto& it : warehouse_.storages_) {
		report.warehouseReport.products[it.first] = it.second.prodCount();
		report.warehouseReport.packages[it.first] = it.second.cargo();
	}

	int finCash = warehouse_.cash_;
	report.warehouseReport.cash = finCash;
	report.warehouseReport.income = finCash - startCash;
	return report;
}

const std::vector<DayReport>& Simulation::genReports(int iters) {
	for (int i = 0; i < iters; ++i) {
		reports_.push_back(this->process());
	}
	return reports_;
}

DayReport Simulation::report() {
#ifdef DEBUG
	std::cout << "REPORT\n\r";
#endif
	DayReport report(warehouse_, consumers_, foodTypes_, consumers_.size());
#ifdef DEBUG
	std::cout << "REPORT COMPLETE\n\r";
#endif
	return report;
}