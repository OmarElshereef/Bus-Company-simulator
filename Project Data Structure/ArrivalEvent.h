#pragma once
#include"Event.h"

class ArrivalEvent:public Event
{
public:
	ArrivalEvent();
	ArrivalEvent(int,int,char);
	char gettype();
	~ArrivalEvent();
};

