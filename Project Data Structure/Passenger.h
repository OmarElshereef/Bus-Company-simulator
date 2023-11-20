#pragma once
#include <iostream>

using namespace std;



class Passenger
{
	int arrivetime;
	int  StartStation, EndStation;
	int PassengerType;
	int PassengerId;
	string PassType;

public:
	Passenger(string passtype = "NP");
	


	int getPassengerID();
	
	void setPassengerID(int id);
	
	~Passenger();
	
};
