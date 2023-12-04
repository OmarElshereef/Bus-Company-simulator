#include "LeaveEvent.h"

LeaveEvent::LeaveEvent() : Event()
{
}

LeaveEvent::LeaveEvent(int t=0,int i=0,char c='a') : Event(t,i, c)
{
}

bool LeaveEvent::execute(Station** list)
{
	bool is = false;
	
	
		is = list[station]->exitpassenger(ID);

		return is;
}

void LeaveEvent::display()
{
	
}

void LeaveEvent::setstation(int st)
{
	station = st;
}

char LeaveEvent::gettype()
{
	return type;
}

LeaveEvent::~LeaveEvent()
{
}
