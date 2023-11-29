#include "Event.h"

Event::Event()
{
}

Event::Event(int t,int I,char c)
{
	ID = I;
	time = t;
	type = c;
}

int Event::gettime()
{
	return time;
}

int Event::getID()
{
	return ID;
}

void Event::setID(int I)
{
	ID = I;
}

void Event::settime(int t)
{
	time = t;
}

void Event::settype(char c)
{
	type = c;
}

void Event::display()
{
	cout << type << " " << ID << " " << time << endl;
}

Event::~Event()
{
}
