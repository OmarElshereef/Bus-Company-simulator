#include "Passenger.h"
#include"UI.h"

int Passenger::Bus_GetOnTime = 0;
int Passenger::maxWait = 0;

bool Passenger::operator==(Passenger& Pto)
{
	if (PassengerId == Pto.getPassengerID())
		return true;
	else
		return false;
}

void Passenger::operator=(Passenger& Pto)
{
	PassengerType = Pto.GetPassengerType();
	arrivetime = Pto.getarrivetime();
	PassengerId = Pto.getPassengerID();
	StartStation = Pto.GetStartStation();
	CurrentStation = Pto.GetCurrentStation();
	EndStation = Pto.GetEndStation();
	PassengerPriority = Pto.GetPassengerPriority();
}

bool Passenger::getdirection()
{
	return direction;
}

Passenger::Passenger(string passtype , int PassID , int Start , int End, string PriorityType, int arriving)
{
	PassengerType = passtype;

	arrivetime = arriving;

	PassengerId = PassID;

	StartStation = CurrentStation = Start;

	EndStation = End; 

	SetPassengerPriority(PriorityType);

	if (Start<End)
	{
		direction = true;
	}
	else
	{
		direction = false;
	}

	promoted = false;
}

void Passenger::SetUI(UI* printer)
{
}

void Passenger::SetPassengerType(string Type)
{
	PassengerType = Type;
}

bool Passenger::getpromoted()
{
	return promoted;
}

void Passenger::setpromoted(bool p)
{
	promoted = p;
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
		else if(type == "pregnantwomen")
		{
			PassengerPriority = 1;
		}
	}
}

void Passenger::display()
{
	//printer.Print(PassengerId);
	//printer.Print("  ");
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

int Passenger::getmaxwait()
{
	return maxWait;
}

int Passenger::getarrivetime()
{
	return arrivetime;
}

int Passenger::getmovetime()
{
	return movetime;
}

void Passenger::setmovetime(int t)
{
	movetime = t;
}

int Passenger::GetCurrentStation()
{
	return CurrentStation;
}

string Passenger::GetPassengerType()
{
	return PassengerType;
}

int Passenger::GetPassengerPriority()
{
	return PassengerPriority;
}

void Passenger::UpgradePriority()
{
	if (PassengerPriority == 0)
	{
		PassengerPriority = 3;
	}

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

void Passenger::setfinishtime(int t)
{
	finishtime = t;
}

int Passenger::getfinishtime()
{
	return finishtime;
}

Passenger ::~Passenger()
{

}
