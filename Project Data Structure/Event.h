#pragma once
#include"Station.h"
#include"Passenger.h"
#include<iostream>
using namespace std;
class Event
{
protected:
	int time;
	char type;
	int ID;
public:
	Event();
	Event(int,int,char);
	virtual int gettime();
	virtual char gettype() = 0;
	virtual int getID();
	virtual void setID(int);
	virtual void settime(int);
	virtual void settype(char);
    virtual void display() =0;
	virtual bool execute(Station**, int) =0;
	~Event();
};

