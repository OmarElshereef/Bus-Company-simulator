#pragma once
#include<random>
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
	fifoqueue<Passenger*> finished_queue;
	Bus** Busses_arr;
	int count_busses;
	int time;
	int lines_read;
	bool executeevent();
	void updatebusses();
public:

	Company();
	
	void readFile();
	bool takeinpassenger();
	void simulation();
	void simulate_phase_1();
	void updatestations();
	void display();
	~Company();
	
};
