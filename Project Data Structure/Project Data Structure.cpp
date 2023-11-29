#include"Company.h"
#include"fifoqueue.h"
#include"priorityqueue.h"
#include"Node.h"
#include"Station.h"
#include <iostream>

using namespace std;

int main()
{
	Company c;
	c.readFile();
	priorityqueue<Passenger> q;

	//Station s(0);
	//s.insertpassenger();

	//Bus b(40,10,1,1,'W'); //size, max_trips, bus_number, station_number, type

	//b.display_bus();
}

