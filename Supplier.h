#pragma once
#include "ITransferPoint.h"
#include "Commands.h"
#include <unordered_map>

class Supplier : public ITransferPoint {
public:
	Supplier();
	static std::unordered_map<std::string, const Supplier> list;
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

	friend class Simulation;
};