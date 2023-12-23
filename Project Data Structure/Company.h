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
#include"UI.h"
using namespace std;

class Company
{
private:
	UI printer;
	Station** stationList;
	int stationNum;
	fifoqueue<Event*>simevents;
	fifoqueue<Passenger*> population;
	fifoqueue<Passenger*> finished_queue;
	Bus** Busses_arr;
	int count_busses;
	int count_Mbus;
	int count_wbus;
	int time;
	int lines_read;
	bool executeevent();
	void updatebusses();
public:

	Company();
	
	void readFile();

	void writeFile();

	bool takeinpassenger();

	void simulation();

	void simulate_phase_1();

	void updatestations();

	void display();

	~Company();
	
};
