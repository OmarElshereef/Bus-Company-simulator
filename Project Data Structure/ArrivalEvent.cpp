#include "ArrivalEvent.h"

ArrivalEvent::ArrivalEvent() : Event()
{
}

ArrivalEvent::ArrivalEvent(int t=0,int i=0,char c='a') : Event(t,i,c)
{
}

void ArrivalEvent::setdata(string type, string dis, int from, int to)
{
	StartStation = from;
	EndStation = to;
	PassengerType = type;
	disability = dis;
}

Passenger* ArrivalEvent::execute()
{
	Passenger* temp = new Passenger(PassengerType, ID, StartStation, EndStation, disability, time);
	return temp;
}


char ArrivalEvent::gettype()
{
	return type;
}

ArrivalEvent::~ArrivalEvent()
{
}
