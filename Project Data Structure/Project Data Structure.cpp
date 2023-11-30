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
	Passenger* p;
	Station s(0);
	while (!c.population.isempty())
	{
		c.population.pop(p);
		s.insertpassenger(p);
	}
	s.displayinfo();
	s.promotePassengers(283);
	s.displayinfo();

	//Bus b(40,10,1,1,'W'); //size, max_trips, bus_number, station_number, type

	//b.display_bus();
}

