#include<iostream>
#include<fstream>
#include"Passenger.h"
#include"bus.h"
#include"ArrivalEvent.h"
#include"LeaveEvent.h"
#include"fifoqueue.h"

using namespace std;

class Company
{
private:

	//fifoqueue<ArrivalEvent> arrivals;
	//fifoqueue<Passenger> population;
	//fifoqueue<LeaveEvent> leaves;

public:
	Company();
	
	void readFile();

	~Company();
	
};
