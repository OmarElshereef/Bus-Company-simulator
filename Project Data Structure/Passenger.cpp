#include "Passenger.h"

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




Passenger ::~Passenger()
{

}
