#pragma once
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
private:
	bool isFirst_ = true;
	int cash_ = 1000000;
	Supplier* supp_;
	std::unordered_map<std::string, int> dayDemand_;
	std::unordered_map<std::string, int> demand_;
	std::unordered_map<std::string, Storage> storages_ = {
		{ "egg", Storage("egg", 250) },
		{ "fish", Storage("fish", 250) },
		{ "meat", Storage("meat", 250) },
		{ "apple", Storage("apple", 250) },
		{ "pear", Storage("pear", 250) },
		{ "milk", Storage("milk", 250) },
		{ "water", Storage("water", 250) },
		{ "bread", Storage("bread", 250) },
		{ "cake", Storage("cake", 250) },
		{ "napkins", Storage("napkins", 250) },
		{ "soap", Storage("soap", 250) },
		{ "shampoo", Storage("shampoo", 250) },
		{ "coal", Storage("coal", 250) }
	};
	std::vector<Request> requests_;
	// Implementation
	std::string name() override;
	void processRequest(Request req) override;
	void processAnswer(Answer ans) override;
	void processOrder(Order ord) override;
	void processTransmission(Transmission trans) override;
	void request(Request req, ITransferPoint* dest) override;
	void answer(Answer ans, ITransferPoint* dest) override;
	void order(Order ord, ITransferPoint* dest) override;
	void transmit(Transmission trans) override;
};