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
		int i = 0;
		for (auto& jt : it.second.store_) {
			jt.rot();
			if (jt.isRotten()) {
				auto iter = it.second.store_.begin();
				std::advance(iter, i);
				it.second.store_.erase(iter);
			}
			++i;
		}
	}
}

void Warehouse::process() {
	for (auto it : dayDemand_) {
		it.second = 0;
	}
	for (auto it : requests_) {
		dayDemand_[it.type] += it.count;
	}
	if (isFirst_) {
		demand_ = dayDemand_;
		isFirst_ = false;
	}
	/*
	* Warehouse -> Consumers
	*/
	for (auto it : dayDemand_) {
		demand_[it.first] = (demand_[it.first] + dayDemand_[it.first]) / 2;
		int diff = demand_[it.first] * 3 - storages_[it.first].prodCount();
		if (diff > 0 && diff >= 50) {
			request(Request(it.first, demand_[it.first] * 3, this), supp_);
		}
	}
}

// Implementation
const std::string& Warehouse::name() {
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