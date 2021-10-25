#include "Warehouse.h"
#include <random>

Warehouse::Warehouse(Supplier* supp) : 
	supp_(supp) {
	for (int i = 0; i < Product::names.size(); ++i) {
		demand_.insert({ Product::names[i], 0 });
		dayDemand_.insert({ Product::names[i], 0 });
	}
}

void Warehouse::rot() {
	for (auto& it : storages_) {
		auto jt = it.second.store_.begin();
		for (int i = 0; i < it.second.cargo_; ++i, ++jt) {
			jt->rot();
			if (jt->isRotten()) {
				it.second.get(i--);
			}
		}
	}
}

void Warehouse::process() {
	for (auto& it : dayDemand_) {
		it.second = 0;
	}
	for (auto& it : requests_) {
		dayDemand_[it.type] += it.count;
	}
	if (isFirst_) {
		demand_ = dayDemand_;
		isFirst_ = false;
	}
	auto ordersRemaining = dayDemand_;
	for (auto& it : requests_) {
		if (ordersRemaining[it.type] < storages_[it.type].prodCount()) {
			answer(Answer(it.type, true, it.count, this), it.dest);
		} else {
			answer(Answer(it.type, false, it.count, this), it.dest);
		}
		
	}
	requests_.clear();
	for (auto& it : dayDemand_) {
		demand_[it.first] = (demand_[it.first] + dayDemand_[it.first]) / 2;
		int diff = demand_[it.first] * 3 - storages_[it.first].prodCount();
		if (diff > 0 && diff >= 50) {
			request(Request(it.first, demand_[it.first] * 3, this), supp_);
		}
	}
}

// Implementation
std::string Warehouse::name() {
	return "warehouse";
}

void Warehouse::processRequest(Request req) {
	requests_.push_back(req);
}

void Warehouse::processAnswer(Answer ans) {
	std::uniform_real_distribution<double> priceKoef(0.75, 0.9);
	std::random_device rand_dev;
	std::mt19937 rand_engine(rand_dev());
	int price = ans.count * Product::list[ans.type].price() * priceKoef(rand_engine);
	if (price > cash_)
		return;
	order(Order(ans.type, price, ans.count, this), ans.dest);
}

void Warehouse::processOrder(Order ord) {
	cash_ += ord.price;
	transmit(Transmission(std::vector<Package>{Package(Product::list[ord.type], ord.count) }, ord.dest, 1));
}

void Warehouse::processTransmission(Transmission trans) {
	for (auto& pack : trans.packs) {
		if (!storages_[pack.name()].add(pack)) {
			break;
		}
		storages_[pack.name()].setVCargo(storages_[pack.name()].getVCargo() - 1);
	}
}

void Warehouse::request(Request req, ITransferPoint* dest) {
	dest->processRequest(req);
}

void Warehouse::answer(Answer ans, ITransferPoint* dest) {
	dest->processAnswer(ans);
}

void Warehouse::order(Order ord, ITransferPoint* dest) {
	cash_ -= ord.price;
	dest->processOrder(ord);
}

void Warehouse::transmit(Transmission trans) {
	TransferService::addTrans(trans);
}