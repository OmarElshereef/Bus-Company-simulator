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
	fifoqueue<Bus*> MBusInStationForward;
	fifoqueue<Bus*> WBusInStationForward;
	fifoqueue<Bus*> MBusInStationBackward;
	fifoqueue<Bus*> WBusInStationBackward;
	priorityqueue<Passenger*> stationpassengersForward;
	fifoqueue<Passenger*> WheelChairQForward;
	priorityqueue<Passenger*> stationpassengersBackward;
	fifoqueue<Passenger*> WheelChairQBackward;

public:
	Station(int);
	
	
	void displayinfo();
	
	
	void setTravelDistance(int);
	
	
	void promotePassengers(int);
	
	
	void insertpassenger(Passenger*);
	
	void EnqueueBus(Bus* incoming);

	~Station(); 
};

