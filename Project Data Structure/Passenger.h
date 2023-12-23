#pragma once
#include <iostream>
#include"UI.h"
using namespace std;

class Passenger
{
	UI printer;
	static int Bus_GetOnTime;
	static int maxWait;

	int  StartStation,CurrentStation ,EndStation;
	
	int PassengerPriority; //0 for normal , 1 for pregnant women, 2 for POD,3 for Aged 
	
	int PassengerId;
	
	int arrivetime;

	int finishtime;

	bool promoted;

	int movetime;

	string PassengerType; //NP for normal passenger,SP for special passenger , WP for wheel chair passenger

	bool direction;

public:
	
	Passenger(string passtype = "NP", int PassID = 0, int Start = 0, int End=0, string PriorityType = "no priority", int arriving=0);
	
	void SetPassengerType(string Type);

	bool getpromoted();

	void setpromoted(bool);

	void SetPassengerPriority(string type);

	void UpgradePriority();

	void setPassengerID(int id);

    int getPassengerID();

	int GetStartStation();

	int GetEndStation();

	int getmaxwait();

	int getarrivetime();

	int getmovetime();

	void setmovetime(int);

	int GetCurrentStation(); 

	string GetPassengerType();

	int GetPassengerPriority();

	static void setgetontime(int);

	static void setmaxwait(int);

	void setfinishtime(int);

	int getfinishtime();

	void display();
	
	bool operator == (Passenger&);
	
	void operator = (Passenger&);
	
	bool getdirection();

	~Passenger();	
};
