#include "LeaveEvent.h"

LeaveEvent::LeaveEvent() : Event()
{
}

LeaveEvent::LeaveEvent(int t=0,int i=0,char c='a') : Event(t,i, c)
{
}

char LeaveEvent::gettype()
{
	return type;
}

LeaveEvent::~LeaveEvent()
{
}
