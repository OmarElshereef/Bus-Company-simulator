#include"Company.h"
#include"fifoqueue.h"
#include"priorityqueue.h"
#include"Node.h"
#include <iostream>
using namespace std;

int main()
{
	Company c;
	c.readFile();

	Bus b; //size, max_trips, bus_number, station_number, type

	b.display_bus();
}

