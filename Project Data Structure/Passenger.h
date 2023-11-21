#pragma once
#include <iostream>

using namespace std;



class Passenger
{
	int arrivetime;

	int Bus_GetOnTime;

	int  StartStation,CurrentStation ,EndStation;
	
	int PassengerPriority; //0 for normal , 1 for pregnant women, 2 for POD,3 for Aged 
	
	int PassengerId;
	
	string PassengerType; //NP for normal passenger,SP for special passenger , WP for wheel chair passenger

public:
	
	Passenger(string passtype = "NP", int PassID = 0, int Start = 0, int End=0, string PriorityType = "no priority");
	
	void SetPassengerType(string Type);

	void SetPassengerPriority(string type);

	void UpgradePriority();

	void setPassengerID(int id);

    int getPassengerID();

	int GetStartStation();

	int GetEndStation();

	int GetCurrentStation(); 

	int GetPassengerPriority();

	void displayData();
	
	~Passenger();
	
};
