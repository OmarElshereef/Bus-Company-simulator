#pragma once
#include<iostream>
using namespace std;

class Event
{
protected:
	int time;
	char type;
public:
	Event();
	Event(int,char);
	virtual int gettime();
	virtual char gettype() = 0;
	virtual void settime(int);
	virtual void settype(char);
    virtual void display();
	~Event();
};

