#pragma once
#include"Event.h"
#include"Passenger.h"
#include"Station.h"

class ArrivalEvent:public Event
{
	int  StartStation, CurrentStation, EndStation;

	int PassengerPriority; //0 for normal , 1 for pregnant women, 2 for POD,3 for Aged 

	string PassengerType; //NP for normal passenger,SP for special passenger , WP for wheel chair passenger
	string disability;
	bool direction;

public:
	ArrivalEvent();
	ArrivalEvent(int,int,char);
	void setdata(string,string,int,int);
	bool execute(Station**,int);
	void display();
	char gettype();
	~ArrivalEvent();
};

