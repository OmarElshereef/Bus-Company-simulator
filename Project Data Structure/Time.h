#pragma once
#include <iostream> 
using namespace std;
class Time
{
	int hour;

	int minute;

public:

	Time(int h, int m)
	{
		hour = h;
		minute = m;
	}

	void AdvanceTime(int m)
	{
		minute = m + minute;

		if (minute >= 60)
		{
			hour = hour + (minute / 60);

			minute = minute - ((minute / 60) * 60);
		}

		if (hour > 24)
		{
			hour = hour % 24;
		}

	}

	~Time()
	{

	}
};

