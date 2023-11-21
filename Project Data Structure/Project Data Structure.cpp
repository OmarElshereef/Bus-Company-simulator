#include"Company.h"
#include <iostream>
using namespace std;

int main()
{
	Company c;
	c.readFile();

	Bus b(40,10,1,1,'W'); //size, max_trips, bus_number, station_number, type

	b.display_bus();
}

