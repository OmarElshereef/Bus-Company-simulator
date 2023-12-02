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

bool ArrivalEvent::execute(Station** list)
{
	Passenger* temp = new Passenger(PassengerType, ID, StartStation, EndStation, disability, time);
	

	list[temp->GetStartStation()]->insertpassenger(temp);
	//list[temp->GetStartStation()]->displayinfo();
	return true;
}

void ArrivalEvent::display()
{
	cout << type << " " << ID << " " << time << endl;
}


char ArrivalEvent::gettype()
{
	return type;
}

ArrivalEvent::~ArrivalEvent()
{
}
