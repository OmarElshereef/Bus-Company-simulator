#pragma once
#include<iostream>
#include<fstream>
#include"Event.h"
#include"ArrivalEvent.h"
#include"LeaveEvent.h"
#include"Passenger.h"
#include"Station.h"
#include"Bus.h"

using namespace std;

class Company
{
private:
	Station** stationList;
	int stationNum;
	fifoqueue<Event*>simevents;
	fifoqueue<Passenger*> population;
	fifoqueue<Passenger*>* finished_queue;
	Bus** Busses_arr;
	int count_busses;
	int timestep[2]; // timestep in hh:mm 
	// company working hours: 4:00 to 22:00
	int time;
	void executeevent();
	void updatebusses();
public:

	Company();
	
	void readFile();
	bool takeinpassenger();
	void simulation();
	void time_up();

	int get_time();

	void set_time(int hh, int mm); // if needed

	void display();
	~Company();
	
};
