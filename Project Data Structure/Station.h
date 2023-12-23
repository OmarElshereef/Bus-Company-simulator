#pragma once
#include"Bus.h"
#include"Passenger.h"
#include"fifoqueue.h"
#include"priorityqueue.h"
#include"UI.h"

class Station
{
private:
	UI printer;
	static int travel_distance;
	const int number;
	static int station_count;
	static int boardTime;
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
	
	bool exitpassenger(int);

	void exitpassengerbytype(Passenger*&, int);

	void displayinfo();
	
	void setTravelDistance(int);
	
	void promotePassengers(int);
	
	void insertpassenger(Passenger*);
	
	void EnqueueBus(Bus* incoming,fifoqueue<Passenger*> &finished_queue);

	void DequeueBus(int curr_time);

	static void setstationcount(int);

	void setboardtime(int);

	void refreshstation(fifoqueue<Passenger*>& finished_queue);
	~Station(); 
};

