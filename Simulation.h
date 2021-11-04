#pragma once
#include "debug.h"
#include "Supplier.h"
#include "Consumer.h"
#include "Warehouse.h"
#include <vector>

struct WarehouseReport_ {
	// Скока прибыли
	int income = 0;
	// Скока денег у склада
	int cash = 0;
	// Скока приехало продуктов
	std::unordered_map<std::string, int> get;
	// Скока бракованных продуктов
	std::unordered_map<std::string, int> defects;
	// Скока испортившихся продуктов
	std::unordered_map<std::string, int> rotten;
	// Скока всего продуктов
	std::unordered_map<std::string, int> products;
	// Скока упаковок продуктов
	std::unordered_map<std::string, int> packages;
	// Спрос за день
	std::unordered_map<std::string, int> demand;
	// Отправленные продукты
	std::unordered_map<std::string, int> sended;
	// Заказанные продукты
	std::unordered_map<std::string, int> requested;
};

struct TransferReport_ {
	// Отправления (смотреть Transmission)
	std::vector<Transmission> trans;
};

struct ConsumerReport_ {
	// Запрошеные продукты
	std::unordered_map<std::string, int> requested;
	// Полученные продукты
	std::unordered_map<std::string, int> sended;
};

class DayReport {
public:
	DayReport(Warehouse warehouse, std::vector<Consumer> consumers, int prodCount, int consume);
	friend std::ostream& operator<<(std::ostream& out, const DayReport& rep);

	WarehouseReport_ warehouseReport;
	TransferReport_ transferReport;
	std::vector<ConsumerReport_> consumersReport;
	int foodTypes;
private:
	Warehouse warehouse_;
	std::vector<Consumer> consumers_;
	std::list<Transmission> packages_;
};

class Simulation {
public:
	Simulation(int consumers, int foodTypes = 10, int warehouseCapacity = 100);
	DayReport process();
	const std::vector<DayReport>& genReports(int iters);

	DayReport report();

	friend int main();
private:
	Simulation();
	int foodTypes_ = 10;
	std::vector<DayReport> reports_;
	Warehouse warehouse_ = Warehouse(nullptr, 100, 10);
	Supplier supplier_;
	std::vector<Consumer> consumers_;
};