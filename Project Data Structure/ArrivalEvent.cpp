#include "ArrivalEvent.h"

ArrivalEvent::ArrivalEvent() : Event()
{
}

ArrivalEvent::ArrivalEvent(int t=0,int i=0,char c='a') : Event(t,i,c)
{
}

char ArrivalEvent::gettype()
{
	return type;
}

ArrivalEvent::~ArrivalEvent()
{
}
