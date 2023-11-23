#pragma once
#include"Bus.h"
#include"Passenger.h"
#include"fifoqueue.h"

class Station
{
	fifoqueue<Bus> BusInStation;
	fifoqueue<Passenger> NormalPassengerQ;
	fifoqueue<Passenger> AgedPassengerQ;
	fifoqueue<Passenger> PODPassengerQ;
	fifoqueue<Passenger> PregnantWomenQ;
	fifoqueue<Passenger> WheelChairQ;

public:
	Station();

	~Station(); 
};

