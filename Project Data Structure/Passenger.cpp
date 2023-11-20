#include "Passenger.h"

Passenger::Passenger(string passtype)
{

	PassType = passtype;
	// ssdsda
}

int Passenger::getPassengerID()
{
	return PassengerId;
}

void Passenger::setPassengerID(int id)
{
	PassengerId = id;
}




Passenger ::~Passenger()
{

}
