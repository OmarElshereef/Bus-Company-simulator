#pragma once
#include"Bus.h"
#include"Passenger.h"
#include"fifoqueue.h"
#include"priorityqueue.h"

class Station
{
private:
	static int travel_distance;
	const int number;
	fifoqueue<Bus> BusInStation;
	priorityqueue<Passenger> stationpassengers;
	//fifoqueue<Passenger> NormalPassengerQ;
	//fifoqueue<Passenger> AgedPassengerQ;
	//fifoqueue<Passenger> PODPassengerQ;
	//fifoqueue<Passenger> PregnantWomenQ;
	fifoqueue<Passenger> WheelChairQ;

public:
	//Station();
	Station(int);
	void displayinfo();
	void setTravelDistance(int);
	void promotePassengers();
	void insertpassenger(Passenger&);
	~Station(); 
};

