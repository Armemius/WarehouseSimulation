#pragma once
#include "debug.h"
#include <list>
#include <iostream>
#include "Commands.h"
#include "ITransferPoint.h"

class Transmission;
class DayReport;

class TransferService {
public:
	static void addTrans(Transmission trans);
	static void process(DayReport& report);
	friend class DayReport;
	friend class Simulation;
	friend std::ostream& operator<<(std::ostream& out, const DayReport& rep);
private:
	TransferService();
	static std::list<Transmission> packages_;
};