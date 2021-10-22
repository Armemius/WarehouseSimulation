#pragma once
#include "Commands.h"
#include "TransferService.h"

class Request;
class Answer;
class Order;
class Transmission;

class ITransferPoint {
public:
	virtual void processRequest(Request req) = 0;
	virtual void processAnswer(Answer ans) = 0;
	virtual void processOrder(Order ord) = 0;
	virtual void processTransmission(Transmission trans) = 0;
	virtual void Request(Request req, ITransferPoint dest) = 0;
	virtual void Answer(Answer ans, ITransferPoint dest) = 0;
	virtual void Order(Order ord, ITransferPoint dest) = 0;
	virtual void Transmit(Transmission trans) = 0;
};