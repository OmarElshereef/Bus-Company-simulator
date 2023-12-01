#pragma once
#include"Passenger.h"
#include"ArrivalEvent.h"
#include"LeaveEvent.h"
#include "fifoqueue.h"


class Bus
{
private:
	Passenger** passenger_arr;
		fifoqueue<Passenger*>* finished_queue;
	
	static int TimeBetweenStations;
    int BC;				   // bus capacity (max # of passengers can a bus carry)
	static int max_trips;   // max trips and then the bus must be unavailable for maintenance
	int curr_trips;		   // # trips after last maintenance
	int num_of_passengers; // # current passengers in the bus
	bool direction;		   // true = forward  false = backward
	bool closed;		   // closed = 1, open = 0
	int station;		   // station number [0,11]
	char bus_type;		   // mixed= M & wheel-chair= W
	int EstimatedTimeOfArrival;   //time to reach the next station
	bool InStation;               //if the bus is instation or not

	int distance; // time for each bus and =0 when arrive station

public:
	Bus(int capacity = 100, int s = 0, char type = 'M');

	~Bus();
	
	void display();

	bool get_door();
	

	void set_door(bool door);
	

	int get_station();
	
	void set_station(int s);

	void set_direction(bool d);

	void upgrade_station();
	

	int get_passengers();
	

	void set_passengers(int p);
	

	bool is_full();
	

	bool is_available();
	

	bool is_mixed_bus();
	

	bool maintenance_time(); // check if a bus need maintenance or not

	int get_distance();
	void set_distance(int d);

	void exit_passenger();

	void remove(int index);
	

	bool enter_passenger(Passenger* p);

	// Adding functions to interact with the Company and Events:


	void setArriveTime(int);

	int getArriveTime();

	void setInStation(bool);

	bool getInStation();

	bool getDirection();

	bool getBusType();

	static bool SetTimeBetweenStations(int);

	static bool SetMaxStations(int);
};