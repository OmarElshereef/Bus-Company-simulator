#pragma once
#include"Event.h"

class ArrivalEvent:public Event
{
public:
	ArrivalEvent();
	ArrivalEvent(int,char);
	char gettype();
	~ArrivalEvent();
};

