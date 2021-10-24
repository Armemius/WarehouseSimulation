#pragma once
#include "ITransferPoint.h"
#include "Storage.h"
#include "Supplier.h"
#include <vector>
#include <unordered_map>

typedef std::tr1::unordered_map<std::string, Storage> hashmap;

class Warehouse : public ITransferPoint {
public:
	Warehouse();
	void test() {
		request(Request("egg", 666, this), &supp_);
	}

	friend int main();
private:
	int cash_ = 1000000;
	Supplier supp_;
	hashmap storages_ = {
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