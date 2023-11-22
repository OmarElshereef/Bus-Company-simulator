#pragma once
#include"Passenger.h"
//#include"Company.h"
#include"ArrivalEvent.h"
#include"LeaveEvent.h"
#include "fifoqueue.h"


class Bus
{
private:
	//Company* company;
	Passenger** passenger_arr;
	fifoqueue<Passenger*>* finished_queue;
	ArrivalEvent* arrivalEvent = new ArrivalEvent;
	LeaveEvent* leaveEvent = new LeaveEvent;
    int BC;		   // bus capacity (max # of passengers can a bus carry)
	const int max_trips;   // max trips and then the bus must be unavailable for maintenance
	int curr_trips;		   // # trips after last maintenance
	int num_of_passengers; // # current passengers in the bus
	int bus_number;		   // In the busses array [0,13]
	bool direction;		   // true = forward  false = backward
	bool closed;		   // closed = 1, open = 0
	int station;		   // station number [0,11]
	char bus_type;		   // mixed= M & wheel-chair= W


public:
	Bus(int size, int max, int bus_num, int s, char type);

	~Bus();
	
	void display_bus();

	bool get_door();
	

	void set_door(bool door);
	

	int get_station();
	

	void set_station(int s);
	

	int get_passengers();
	

	void set_passengers(int p);
	

	bool is_full();
	

	bool is_available();
	

	bool is_mixed_bus();
	

	bool maintenance_time(); // check if a bus need maintenance or not
	

	void remove(int index);
	

	bool enter_passenger(Passenger* p);


	void exit_passenger(Passenger* p, Passenger** finished_array, int& size);

	void set_arrival_event(ArrivalEvent* arrivalEvt);

	void set_leave_event(LeaveEvent* leaveEvt);

	// Adding functions to interact with the Company and Events:
	void arrive_at_station();

	void leave_station();

};