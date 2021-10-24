#pragma once
#include "Warehouse.h"

class Consumer : public ITransferPoint {
public:
	Consumer(Warehouse* warehouse, int types);

	void reloadWeights();
	void process();

	// Implementation
	const std::string& name() override;
	void processRequest(Request req) override;
	void processAnswer(Answer ans) override;
	void processOrder(Order ord) override;
	void processTransmission(Transmission trans) override;
	void request(Request req, ITransferPoint* dest) override;
	void answer(Answer ans, ITransferPoint* dest) override;
	void order(Order ord, ITransferPoint* dest) override;
	void transmit(Transmission trans) override;

	friend class Simulation;
private:
	int types_;
	Warehouse* warehouse_;
	std::unordered_map<std::string, int> weights_;
	std::unordered_map<std::string, int> virtualProducts_;
	std::unordered_map<std::string, int> products_;
};