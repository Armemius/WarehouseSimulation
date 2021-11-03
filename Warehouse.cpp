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
				//it.second.get(i--);
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
		double koef = storages_[it.type].prodCount() * 1.0 / dayDemand_[it.type];
		if (koef == 0) {
			answer(Answer(it.type, false, 0, this), it.dest);
			continue;
		}
		int count;
		if (koef < 1)
			count = it.count * koef;
		else
			count = it.count;
		count = count - count % 25 + std::round(count % 25 / 25.0) * 25;
		int pack100 = 0, pack50 = 0, pack25 = 0;
		for (auto& jt : storages_[it.type].store_) {
			if (jt.count() == 100)
				pack100++;
			else if (jt.count() == 50)
				pack50++;
			else if (jt.count() == 25)
				pack25++;
			else
				throw std::exception("Sussy package");
		}
		int req100 = std::min(count / 100, pack100), 
			req50 = std::min((count - req100 * 100) / 50, pack50),
			req25 = std::min((count - req100 * 100 - req50 * 50) / 25, pack25);
		if (req100 == 0 && req50 == 0 && req25 == 0) {
			answer(Answer(it.type, false, 0, this), it.dest);
			continue;
		}
		int total = req100 * 100 + req50 * 50 + req25 * 25;
		int index = 0;
		std::string type = it.type;
		auto& store = storages_[type].store_;
		auto tmp = *store.begin();
		for (auto& jt : store) {
			if (jt.count() == 100 && req100 > 0) {
				req100--;
				storages_[it.type].get(index--);
			} else if (jt.count() == 50 && req50 > 0) {
				req50--;
				storages_[it.type].get(index--);
			} else if (jt.count() == 25 && req25 > 0) {
				req25--;
				storages_[it.type].get(index--);
			}
			index++;
		}
		answer(Answer(it.type, true, total, this), it.dest);
	}
	requests_.clear();
	for (auto& it : dayDemand_) {
		const std::string name = it.first;
		demand_[name] = (demand_[name] * 9 + dayDemand_[name]) / 10;
		int diff = demand_[name] * 3 - storages_[name].prodCount();
		if (diff >= 50) {
			const int count = std::min(demand_[name] * 3, storages_[name].free() * 100);
			storages_[name].addVCargo(count / 100 + count % 100 / 50 + count % 50 / 25);
			if (count > 500)
				request(Request(it.first, count, this), supp_);
		}
	}
}

// Implementation
std::string Warehouse::name() const {
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
	std::uniform_real_distribution<double> defect(0.0, 1.0);
	std::random_device rand_dev;
	std::mt19937 rand_engine(rand_dev());
	for (auto& pack : trans.packs) {
		if (defect(rand_engine) < 0.05) {
			continue;
		}
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