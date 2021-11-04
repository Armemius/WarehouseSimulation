#pragma once
#include "debug.h"
#include "Warehouse.h"

class Consumer : public ITransferPoint {
public:
	Consumer(Warehouse* warehouse, int types);

	void reloadWeights();
	void process(DayReport* report, int index);

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

	friend class Simulation;
	friend std::ostream& operator<<(std::ostream& out, const DayReport& rep);
private:
	int types_;
	Warehouse* warehouse_;
	std::unordered_map<std::string, int> weights_;
	std::unordered_map<std::string, int> virtualProducts_;
	std::unordered_map<std::string, int> products_;
};