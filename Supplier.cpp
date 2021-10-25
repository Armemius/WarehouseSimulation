#include "Supplier.h"
#include <random>

Supplier::Supplier() = default;

std::string Supplier::name() {
	return "supplier";
}

void Supplier::processRequest(Request req) {
	int count = req.count;
	count -= count % 25;
	answer(Answer(req.type, true, count, this), req.dest);
}

void Supplier::processAnswer(Answer ans) {
	// Not needed
}

void Supplier::processOrder(Order ord) {
	int count = ord.count;
	count -= count % 25;
	std::vector<Package> packs;
	while (count >= 100) {
		packs.push_back(Package(Product::list[ord.type], 100));
		count -= 100;
	}
	while (count >= 50) {
		packs.push_back(Package(Product::list[ord.type], 50));
		count -= 50;
	}
	while (count >= 25) {
		packs.push_back(Package(Product::list[ord.type], 25));
		count -= 250;
	}
	std::uniform_int_distribution<int> randx(1, 3);
	std::random_device rand_dev;
	std::mt19937 rand_engine(rand_dev());
	transmit(Transmission(packs, ord.dest, randx(rand_engine)));
	return;
}

void Supplier::processTransmission(Transmission trans) {
	// Not needed
}

void Supplier::request(Request req, ITransferPoint* dest) {
	dest->processRequest(req);
}

void Supplier::answer(Answer ans, ITransferPoint* dest) {
	dest->processAnswer(ans);
}

void Supplier::order(Order ord, ITransferPoint* dest) {
	dest->processOrder(ord);
}

void Supplier::transmit(Transmission trans) {
	TransferService::addTrans(trans);
}