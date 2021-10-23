#pragma once
#include "ITransferPoint.h"
#include "Storage.h"
#include <vector>
#include <unordered_map>

typedef std::tr1::unordered_map<std::string, Storage> hashmap;

class Warehouse : public ITransferPoint {
public:
	Warehouse();
private:
	int cash_ = 1000000;
	hashmap storages_ = {
		{ "egg", Storage("egg", 1000000) },
		{ "fish", Storage("fish", 1000000) },
		{ "meat", Storage("meat", 1000000) },
		{ "apple", Storage("apple", 1000000) },
		{ "pear", Storage("pear", 1000000) },
		{ "milk", Storage("milk", 1000000) },
		{ "water", Storage("water", 1000000) },
		{ "bread", Storage("bread", 1000000) },
		{ "cake", Storage("cake", 1000000) },
		{ "napkins", Storage("napkins", 1000000) },
		{ "soap", Storage("soap", 1000000) },
		{ "shampoo", Storage("shampoo", 1000000) },
		{ "coal", Storage("coal", 1000000) }
	};
	std::vector<Request> requests_;
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
};