#include "Station.h"
#include<iostream>
using namespace std;

int Station:: travel_distance = 0;


Station::Station(int num):number(num)
{
}

bool Station::exitpassenger(int id)
{
	Passenger* temp = new Passenger("NP", id);
	if (stationpassengersForward.remove(temp))
		return true;
	if (stationpassengersBackward.remove(temp))
		return true;
	if (WheelChairQForward.remove(temp))
		return true;
	if (WheelChairQBackward.remove(temp))
		return true;
	return false;
}

void Station::displayinfo()
{
	cout << "Station number:" << number << endl;
	cout << "people in queue waiting front:" <<endl; stationpassengersForward.print(); WheelChairQForward.print();
	cout << "people in queue waiting back:"<<endl; stationpassengersBackward.print(); WheelChairQBackward.print();
	//cout << "busses in queue waitingm front:";
}

void Station::insertpassenger(Passenger* incoming)
{
	if (incoming->getdirection())
	{
		if (incoming->GetPassengerPriority() == 10)
			WheelChairQForward.push(incoming,10);
		else
			stationpassengersForward.push(incoming, incoming->GetPassengerPriority());
	}
	else
	{
		if (incoming->GetPassengerPriority() == 10)
			WheelChairQBackward.push(incoming,10);
		else
			stationpassengersBackward.push(incoming, incoming->GetPassengerPriority());
	}
}

void Station::EnqueueBus(Bus* incoming)
{
	if (incoming->getDirection())
	{
		if (incoming->getBusType())
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
		if (incoming->getBusType())
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
	if (!stationpassengersForward.isempty())
	{
		fifoqueue<Passenger*> notpromotedQ;
		fifoqueue<Passenger*> promotedQ;
		Passenger* temp;

		while (!stationpassengersForward.isempty())
		{
			stationpassengersForward.pop(temp);
			if (curr_time - temp->getarrivetime() == temp->getmaxwait())
			{
				temp->UpgradePriority();
				promotedQ.push(temp);
			}
			else
				notpromotedQ.push(temp);
		}

		while (!promotedQ.isempty())
		{
			promotedQ.pop(temp);
			stationpassengersForward.push(temp,temp->GetPassengerPriority());
		}

		while (!notpromotedQ.isempty())
		{
			notpromotedQ.pop(temp);
			stationpassengersForward.push(temp, temp->GetPassengerPriority());
		}

		while (!stationpassengersBackward.isempty())
		{
			stationpassengersBackward.pop(temp);
			if (curr_time - temp->getarrivetime() == temp->getmaxwait())
			{
				temp->UpgradePriority();
				promotedQ.push(temp);
			}
			else
				notpromotedQ.push(temp);
		}

		while (!promotedQ.isempty())
		{
			promotedQ.pop(temp);
			stationpassengersBackward.push(temp, temp->GetPassengerPriority());
		}

		while (!notpromotedQ.isempty())
		{
			notpromotedQ.pop(temp);
			stationpassengersBackward.push(temp, temp->GetPassengerPriority());
		}
	}
}

Station::~Station()
{
}
