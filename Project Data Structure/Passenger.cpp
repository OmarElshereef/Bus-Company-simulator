#include "Passenger.h"

int Passenger::Bus_GetOnTime = 0;
int Passenger::maxWait = 0;

Passenger::Passenger(string passtype , int PassID , int Start , int End, string PriorityType )
{

	PassengerType = passtype;

	PassengerId = PassID;

	StartStation =CurrentStation= Start;

	EndStation = End; 

	SetPassengerPriority(PriorityType);
}

void Passenger::SetPassengerType(string Type)
{
	PassengerType = Type;
}

void Passenger::SetPassengerPriority(string type)

{
	if (PassengerType == "NP")
	{
		PassengerPriority = 0;
	}
	else if(PassengerType=="WP")
	{
		PassengerPriority = 10;
	}
	else
	{
		if (type == "aged")
		{
			PassengerPriority = 3; 
		}
		else if(type == "POD")
		{
			PassengerPriority = 2;
		}
		else if(type == "pregnant women")
		{
			PassengerPriority = 1;
		}
	}
}

void Passenger::displayData()
{
	cout << PassengerType << " " << PassengerId << " " << StartStation << " " << EndStation << " "<< PassengerPriority <<" "<< Bus_GetOnTime << " "<< maxWait <<endl;
}

int Passenger::getPassengerID()
{
	return PassengerId;
}

int Passenger::GetStartStation()
{
	return StartStation;
}

int Passenger::GetEndStation()
{
	return EndStation;
}

int Passenger::GetCurrentStation()
{
	return CurrentStation;
}

int Passenger::GetPassengerPriority()
{
	return PassengerPriority;
}

void Passenger::UpgradePriority()
{
	PassengerPriority = 3;
}

void Passenger::setPassengerID(int id)
{
	PassengerId = id;
}

void Passenger::setgetontime(int geton)
{
	Bus_GetOnTime = geton;
}

void Passenger::setmaxwait(int wait)
{
	maxWait = wait;
}

Passenger ::~Passenger()
{

}
