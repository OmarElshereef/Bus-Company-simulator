#pragma once
#include"Passenger.h"
#include"ArrivalEvent.h"
#include"LeaveEvent.h"
#include "fifoqueue.h"


class Bus
{
private:
	//Company* company;

	Passenger** passenger_arr;
	fifoqueue<Passenger*>* finished_queue;
	
	//ArrivalEvent* arrivalEvent = new ArrivalEvent(0,'a');
	//LeaveEvent* leaveEvent = new LeaveEvent(0,'a');
	static int TimeBetweenStations;
    int BC;				   // bus capacity (max # of passengers can a bus carry)
	static int max_trips;   // max trips and then the bus must be unavailable for maintenance
	int curr_trips;		   // # trips after last maintenance
	int num_of_passengers; // # current passengers in the bus
	int bus_number;		   // In the busses array [0,13]
	bool direction;		   // true = forward  false = backward
	bool closed;		   // closed = 1, open = 0
	int station;		   // station number [0,11]
	char bus_type;		   // mixed= M & wheel-chair= W
	int EstimatedTimeOfArrival;   //time to reach the next station
	bool InStation;               //if the bus is instation or not

public:
	Bus(int size = 100, int max = 100,int bus_num=0, int s = 0, char type = 'M');

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
	void exit_passenger(Passenger* p, Passenger** finished_array, int& size);

	

	void remove(int index);
	

	bool enter_passenger(Passenger* p);



	void set_arrival_event(ArrivalEvent* arrivalEvt);

	void set_leave_event(LeaveEvent* leaveEvt);

	// Adding functions to interact with the Company and Events:
	void arrive_at_station();

	void leave_station();

	void setArriveTime(int);

	int getArriveTime();

	void setInStation(bool);

	bool getInStation();

	bool getDirection();

	bool getBusType();

	static bool SetTimeBetweenStations(int);

	static bool SetMaxStations(int);
};