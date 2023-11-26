/**

while(finished queue not completed)
{
	if(station #0 not empty && ! timestep % 15 )
	{
		release a bus from station #0
	}
	for (allBusses)	
	{
		if (allBusses[i].get_distance() == stations_distance)
		{
			allBusses[i].set_distance(0);
			bus get in bus queue in station 

		}
	}
}
*/



#include<iostream>
#include<fstream>
#include"Passenger.h"
#include "Bus.h"
#include"ArrivalEvent.h"
#include"LeaveEvent.h"
#include"fifoqueue.h"

using namespace std;

class Company
{	
private:

	fifoqueue<ArrivalEvent> arrivals;
	fifoqueue<Passenger> population;
	fifoqueue<Bus*> * allBusses;
	fifoqueue<LeaveEvent> leaves;
	Bus ** Busses_arr;
	int count_busses;
	
	int timestep [2] ; // timestep in hh:mm 
					 // company working hours: 4:00 to 22:00

	int stations, distance;
	int wbus, mbus, wbuscap, mbuscap;   //defining varaibles to read data into
	int journies, wbusfix, mbusfix;

public:

	Company();
	
	//int get_buscap();
	//int get_journies();


	void readFile();

	~Company();

	void time_up();
	
	int get_time();

	void set_time(int hh, int mm); // if needed

	void create_busses();
	void release_bus();
	void check_bus_arrival();
	void change_station();

	
};
