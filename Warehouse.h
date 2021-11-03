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
	Warehouse(Supplier* supp);

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
	int cash_ = 1000000;
	Supplier* supp_;
	std::unordered_map<std::string, int> dayDemand_;
	std::unordered_map<std::string, int> demand_;
	std::unordered_map<std::string, Storage> storages_ = {
		{ "egg", Storage("egg", 100) },
		{ "fish", Storage("fish", 100) },
		{ "meat", Storage("meat", 100) },
		{ "apple", Storage("apple", 100) },
		{ "pear", Storage("pear", 100) },
		{ "milk", Storage("milk", 100) },
		{ "water", Storage("water", 100) },
		{ "bread", Storage("bread", 100) },
		{ "cake", Storage("cake", 100) },
		{ "napkins", Storage("napkins", 100) },
		{ "soap", Storage("soap", 100) },
		{ "shampoo", Storage("shampoo", 100) },
		{ "coal", Storage("coal", 100) }
	};
	std::vector<Request> requests_;
};