#include "ArrivalEvent.h"

ArrivalEvent::ArrivalEvent() : Event()
{
}

ArrivalEvent::ArrivalEvent(int t=0,char c='a') : Event(t,c)
{
}

char ArrivalEvent::gettype()
{
	return type;
}

ArrivalEvent::~ArrivalEvent()
{
}
