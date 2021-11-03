#pragma once
#include "debug.h"
#include "Commands.h"
#include "TransferService.h"

class Request;
class Answer;
class Order;
class Transmission;

class ITransferPoint abstract {
public:
	virtual std::string name() const = 0;
	virtual void processRequest(Request req) = 0;
	virtual void processAnswer(Answer ans) = 0;
	virtual void processOrder(Order ord) = 0;
	virtual void processTransmission(Transmission trans) = 0;
	virtual void request(Request req, ITransferPoint* dest) = 0;
	virtual void answer(Answer ans, ITransferPoint* dest) = 0;
	virtual void order(Order ord, ITransferPoint* dest) = 0;
	virtual void transmit(Transmission trans) = 0;
};