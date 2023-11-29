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

	fifoqueue<LeaveEvent> leaves;

public:
	fifoqueue<Passenger> population;
	Company();
	
	void readFile();
	bool takeinpassenger();
	~Company();
	
};
