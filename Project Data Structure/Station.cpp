#include "Station.h"
#include<iostream>
using namespace std;

int Station:: travel_distance = 0;


Station::Station(int num):number(num)
{
}

void Station::displayinfo()
{
	cout << "Station number:" << number << endl;
	//cout<<"people in queue waiting:"<<
	cout << "busses in queue waiting:" << BusInStation.size()<<endl;
}

void Station::insertpassenger(Passenger& incoming)
{
	if (incoming.GetPassengerPriority() == 10)
		WheelChairQ.push(incoming);
	else
		stationpassengers.push(incoming, incoming.GetPassengerPriority());
}

void Station::setTravelDistance(int dist)
{
	travel_distance = dist;
}

void Station::promotePassengers()
{

}

Station::~Station()
{
}
