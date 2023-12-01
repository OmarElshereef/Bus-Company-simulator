#include "LeaveEvent.h"

LeaveEvent::LeaveEvent() : Event()
{
}

LeaveEvent::LeaveEvent(int t=0,int i=0,char c='a') : Event(t,i, c)
{
}

bool LeaveEvent::execute(Station** list, int size,Passenger*& p)
{
	bool is = false;
	for (int i = 0; i < size; i++)
	{
		is = list[i]->exitpassenger(ID);
	}
	return is;
}

void LeaveEvent::display()
{
	cout << type << " " << ID << " " << time << endl;
}

char LeaveEvent::gettype()
{
	return type;
}

LeaveEvent::~LeaveEvent()
{
}
