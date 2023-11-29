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
	fifoqueue<Bus> MBusInStation;
	fifoqueue<Bus> WBusInStation;
	priorityqueue<Passenger> stationpassengers;
	fifoqueue<Passenger> WheelChairQ;

public:
	Station(int);
	void displayinfo();
	void setTravelDistance(int);
	void promotePassengers(int);
	void insertpassenger(Passenger&);
	~Station(); 
};

