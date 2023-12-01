#pragma once
#include"Event.h"
#include"Passenger.h"
#include"Station.h"
class Station;
class LeaveEvent: public Event
{
public:
	LeaveEvent();
	LeaveEvent(int,int,char);
	bool execute(Station**,int);
	char gettype();
	~LeaveEvent();
};

