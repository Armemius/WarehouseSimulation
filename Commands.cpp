#include "Commands.h"

Request::Request(Product type, int count, ITransferPoint* dest) :
	type(type),
	count(count),
	dest(dest){}

Answer::Answer(bool affirmative, int count, ITransferPoint* dest) :
	affirmative(affirmative),
	count(count),
	dest(dest) {}

Order::Order(int price, int count, ITransferPoint* dest) :
	price(price),
	count(count),
	dest(dest) {}

Transmission::Transmission(Package pack, int count, ITransferPoint* dest, int time) :
	pack(pack),
	count(count),
	dest(dest),
	time(time) {}