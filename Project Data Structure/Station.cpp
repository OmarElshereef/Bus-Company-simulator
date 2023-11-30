#include "Station.h"
#include<iostream>
using namespace std;

int Station:: travel_distance = 0;


Station::Station(int num):number(num)
{
}

void Station::displayinfo()
{
	/*cout << "Station number:" << number << endl;
	cout << "people in queue waiting:"; stationpassengers.print();
	cout << "busses in queue waiting:" << BusInStation.size()<<endl;*/
}

void Station::insertpassenger(Passenger& incoming)
{
	if (incoming.getdirection())
	{
		if (incoming.GetPassengerPriority() == 10)
			WheelChairQForward.push(incoming);
		else
			stationpassengersForward.push(incoming, incoming.GetPassengerPriority());
	}
	else
	{
		if (incoming.GetPassengerPriority() == 10)
			WheelChairQBackward.push(incoming);
		else
			stationpassengersBackward.push(incoming, incoming.GetPassengerPriority());
	}
}

void Station::EnqueueBus(Bus& incoming)
{
	if (incoming.getDirection())
	{
		if (incoming.getBusType())
		{
			MBusInStationForward.push(incoming);
		}
		else
		{
			WBusInStationForward.push(incoming);
		}
	}
	else
	{
		if (incoming.getBusType())
		{
			MBusInStationBackward.push(incoming);
		}
		else
		{
			WBusInStationBackward.push(incoming);
		}
	}
}

void Station::setTravelDistance(int dist)
{
	travel_distance = dist;
}

void Station::promotePassengers(int curr_time)
{
	stationpassengersForward.promote(curr_time);

	stationpassengersBackward.promote(curr_time);
}

Station::~Station()
{
}
