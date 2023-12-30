#pragma once

#include<iostream> 
#include<string>

//Forward declaration
class Company;
class Station;
class Bus;
class Passenger;

template<typename T>
class fifoqueue;

template <class T>
class priorityqueue;

using namespace std;

class UI
{
	static int sim;

public : 

	UI()
	{
	}

	int getsim()
	{
		return sim;
	}

	template <typename t > 
	void Print(t object)
	{
		cout << object;
	}

	void welcome()
	{
		Print("welcome!\nselect a simulation mode:\n1)interactive mode\n2)silent mode\n");
		cin >> sim;
		getchar();
	}
	
	void bus_display(int bus_numbber, bool direction, int num_of_passengers, Passenger** passenger_arr);


	void displaycheckup(fifoqueue<Bus*> MBusInStationForward, fifoqueue<Bus*> MBusInStationBackward, fifoqueue<Bus*> WBusInStationBackward, fifoqueue<Bus*> WBusInStationForward, int number);
	
	void display_station_info(fifoqueue<Bus*> MBusInStationForward,
		fifoqueue<Bus*> MBusInStationBackward,
		fifoqueue<Bus*> WBusInStationBackward,
		fifoqueue<Bus*> WBusInStationForward,
		priorityqueue<Passenger*> stationpassengersForward,
		fifoqueue<Passenger*> WheelChairQForward,
		priorityqueue<Passenger*> stationpassengersBackward,
		fifoqueue<Passenger*> WheelChairQBackward,
		int number);
	void display_stations_and_finished_queue(int stationNum, fifoqueue<Passenger*> finished_queue, Station** stationList, int time);
	
	void Print_error();
	void getchar();
	void silent_mode();
	void simulation_ends();	
};


