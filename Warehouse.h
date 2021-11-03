#pragma once
#include "debug.h"
#include "ITransferPoint.h"
#include "Storage.h"
#include "Supplier.h"
#include <vector>
#include <unordered_map>

class Report;

class Warehouse : public ITransferPoint {
public:
	Warehouse(Supplier* supp, int capacity, int foodTypes);

	void rot();
	void process();

	friend class Simulation;
	friend std::ostream& operator<<(std::ostream& out, const Report& rep);

	// Implementation
	std::string name() const override;
	void processRequest(Request req) override;
	void processAnswer(Answer ans) override;
	void processOrder(Order ord) override;
	void processTransmission(Transmission trans) override;
	void request(Request req, ITransferPoint* dest) override;
	void answer(Answer ans, ITransferPoint* dest) override;
	void order(Order ord, ITransferPoint* dest) override;
	void transmit(Transmission trans) override;
private:
	bool isFirst_ = true;
	int cash_ = 5000000;
	int capacity_ = 100;
	Supplier* supp_;
	std::unordered_map<std::string, int> dayDemand_;
	std::unordered_map<std::string, int> demand_;
	std::unordered_map<std::string, Storage> storages_;
	std::vector<Request> requests_;
};