#include<iostream>
#include<fstream>
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
	fifoqueue<ArrivalEvent> arrivals;
	fifoqueue<Passenger*> population;
	fifoqueue<Passenger*>* finished_queue;
	fifoqueue<LeaveEvent> leaves;
	Bus** Busses_arr;
	int count_busses;
	int timestep[2]; // timestep in hh:mm 
	// company working hours: 4:00 to 22:00
	
	int stations, distance;
	int wbus, mbus, wbuscap, mbuscap;   //defining varaibles to read data into
	int journies, wbusfix, mbusfix;
	int maxwait, geton;

public:

	Company();
	
	void readFile();
	bool takeinpassenger();

	void time_up();

	int get_time();

	void set_time(int hh, int mm); // if needed

	void display();

	void create_busses();
	void check_bus_arrival();
	void change_station();

	~Company();
	
};
