#pragma once
#include"Bus.h"
#include"Passenger.h"
#include"fifoqueue.h"
#include"priorityqueue.h"
#include"UI.h"

class Station
{
private:
	UI printer;                       //print using ui class
	static int travel_distance;       //travel distance between each station
	const int number;                //number of the current station
	static int station_count;        //number of stations in total
	static int boardTime;            //geton/off time
	fifoqueue<Bus*> MBusInStationForward;      //Mbusses in station heading forward
	fifoqueue<Bus*> WBusInStationForward;       //Wbusses in station heading backwards
	fifoqueue<Bus*> MBusInStationBackward;      //Mbusses in station heading forward
	fifoqueue<Bus*> WBusInStationBackward;        //Wbusses in station heading backwards
	priorityqueue<Passenger*> stationpassengersForward;      //normal passengers going forward
	fifoqueue<Passenger*> WheelChairQForward;             //wheel chair passengers going forward
	priorityqueue<Passenger*> stationpassengersBackward;     //normal passengers going backward
	fifoqueue<Passenger*> WheelChairQBackward;         //wheel chair passengers going backward

public:
	Station(int);
	
	bool exitpassenger(int);

	void exitpassengerbytype(Passenger*&, int);

	void displayinfo();
	
	void setTravelDistance(int);
	
	void promotePassengers(int);
	
	void insertpassenger(Passenger*);
	
	void EnqueueBus(Bus* incoming);

	void DequeueBus(int curr_time);

	static void setstationcount(int);

	void setboardtime(int);

	void refreshstation(fifoqueue<Passenger*>& finished_queue, int curr_time);
	~Station(); 
};

