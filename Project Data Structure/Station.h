#pragma once
#include"Bus.h"
#include"Passenger.h"
#include"fifoqueue.h"
#include"priorityqueue.h"
class Bus;
class Station
{
private:
	static int travel_distance;
	const int number;
	fifoqueue<Bus*> MBusInStationForward;
	fifoqueue<Bus*> WBusInStationForward;
	fifoqueue<Bus*> MBusInStationBackward;
	fifoqueue<Bus*> WBusInStationBackward;
	priorityqueue<Passenger*> stationpassengersForward;
	priorityqueue<Passenger*> WheelChairQForward;
	priorityqueue<Passenger*> stationpassengersBackward;
	priorityqueue<Passenger*> WheelChairQBackward;

public:
	Station(int);
	
	bool exitpassenger(int);

	void displayinfo();
	
	void setTravelDistance(int);
	
	void promotePassengers(int);
	
	void insertpassenger(Passenger*);
	
	void EnqueueBus(Bus* incoming);

	~Station(); 
};

