#pragma once
#include"Event.h"

class LeaveEvent: public Event
{
public:
	LeaveEvent();
	LeaveEvent(int,int,char);
	char gettype();
	~LeaveEvent();
};

