#pragma once
#include<iostream> 
#include<string>
#include "Station.h"



using namespace std;
class UI
{
	Station* station;
	Bus* bus;
	Passenger* passenger;


public : 

	UI();

	void dispalystation();

	void displaybus();

	void displaypassenger();
	
	

};

