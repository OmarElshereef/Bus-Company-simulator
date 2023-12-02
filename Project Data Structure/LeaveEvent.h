#pragma once
#include"Event.h"
#include"Passenger.h"
#include"Station.h"

class LeaveEvent: public Event
{
	int station;
public:
	LeaveEvent();
	LeaveEvent(int,int,char);
	bool execute(Station**);
	char gettype();
	void display();
	void setstation(int st);
	~LeaveEvent();
};

