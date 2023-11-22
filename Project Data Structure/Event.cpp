#include "Event.h"

Event::Event()
{
}

Event::Event(int t,char c)
{
	time = t;
	type = c;
}

int Event::gettime()
{
	return time;
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
	cout << type << " " << time << endl;
}

Event::~Event()
{
}
