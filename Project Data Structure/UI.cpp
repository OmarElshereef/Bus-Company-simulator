#include "UI.h"
#include "Bus.h"
#include"Station.h"
#include "Passenger.h"
#include"Company.h"
#include"fifoqueue.h" 
#include"priorityqueue.h" 

int UI::sim = 0;

void UI::bus_display(int bus_numbber, bool direction, int num_of_passengers, Passenger** passenger_arr)
{
		Print("BUS" + to_string(bus_numbber) + "[");
		if (direction)
			Print("FWD, ");
		else
			Print("BCK, ");

		Print("] {");
		for (int i = 0; i < num_of_passengers - 1; i++)
		{
			Print(to_string(passenger_arr[i]->getPassengerID()) + ", ");
		}
		if (num_of_passengers != 0)
			Print(to_string(passenger_arr[num_of_passengers - 1]->getPassengerID()));
		Print("}\n");
}


void UI::displaycheckup(fifoqueue<Bus*> MBusInStationForward, fifoqueue<Bus*> MBusInStationBackward, fifoqueue<Bus*> WBusInStationBackward, fifoqueue<Bus*> WBusInStationForward, int number)
{
	
	Bus* bebe;
	fifoqueue<Bus*> temp;
	while (!MBusInStationForward.isempty())
	{
		MBusInStationForward.pop(bebe);
		if (bebe->getmaintain())
			Print(to_string(bebe->getnumber()) + ", ");
		temp.push(bebe);
	}

	while (!temp.isempty())
	{
		temp.pop(bebe);
		MBusInStationForward.push(bebe);
	}

	while (!MBusInStationBackward.isempty())
	{
		MBusInStationBackward.pop(bebe);
		if (bebe->getmaintain())
			Print(to_string(bebe->getnumber()) + ", ");
		temp.push(bebe);
	}

	while (!temp.isempty())
	{
		temp.pop(bebe);
		MBusInStationBackward.push(bebe);
	}

	while (!WBusInStationForward.isempty())
	{
		WBusInStationForward.pop(bebe);
		if (bebe->getmaintain())
			Print(to_string(bebe->getnumber()) + ", ");
		temp.push(bebe);
	}

	while (!temp.isempty())
	{
		temp.pop(bebe);
		WBusInStationForward.push(bebe);
	}

	while (!WBusInStationBackward.isempty())
	{
		WBusInStationBackward.pop(bebe);
		if (bebe->getmaintain())
			Print(to_string(bebe->getnumber()) + ", ");
		temp.push(bebe);
	}

	while (!temp.isempty())
	{
		temp.pop(bebe);
		WBusInStationBackward.push(bebe);
	}
	Print("\n");
}

void UI::display_station_info(fifoqueue<Bus*> MBusInStationForward, fifoqueue<Bus*> MBusInStationBackward, fifoqueue<Bus*> WBusInStationBackward, fifoqueue<Bus*> WBusInStationForward, priorityqueue<Passenger*> stationpassengersForward, fifoqueue<Passenger*> WheelChairQForward, priorityqueue<Passenger*> stationpassengersBackward, fifoqueue<Passenger*> WheelChairQBackward, int number)
{
	Print("==============Station#" + to_string(number) + "=================\n");

	Print(stationpassengersForward.sizebypri(3) + stationpassengersForward.sizebypri(2) + stationpassengersForward.sizebypri(1) + stationpassengersBackward.sizebypri(3) + stationpassengersBackward.sizebypri(2) + stationpassengersBackward.sizebypri(1));

	Print("  Waiting SP: FWD[");

	if (stationpassengersForward.PrintByPriority(3))
		Print("(AG) , ");
	if (stationpassengersForward.PrintByPriority(2))
		Print("(PD) , ");
	if (stationpassengersForward.PrintByPriority(1))
		Print("(PW)");

	Print("]  BCK[");

	if (stationpassengersBackward.PrintByPriority(3))
		Print("(AG) , ");
	if (stationpassengersBackward.PrintByPriority(2))
		Print("(PD) , ");
	if (stationpassengersBackward.PrintByPriority(1))
		Print("(PW)");

	Print("]\n");

	Print(stationpassengersForward.sizebypri(0) + stationpassengersBackward.sizebypri(0));

	Print("  Waiting NP: FWD[");

	stationpassengersForward.PrintByPriority(0);

	Print("]  BCK[");

	stationpassengersBackward.PrintByPriority(0);

	Print("]\n");

	Print(WheelChairQBackward.sizebypri(10) + WheelChairQForward.sizebypri(10));

	Print("  Waiting WP: FWD[");

	WheelChairQForward.PrintByPriority(10);

	Print("]  BCK[");

	WheelChairQBackward.PrintByPriority(10);

	Print("]\n");

	int total = MBusInStationForward.size() + MBusInStationBackward.size() + WBusInStationForward.size() + WBusInStationBackward.size();
	Print(to_string(total) + " in this station:\n");
	fifoqueue<Bus*> temp;
	Bus* bebe;
	while (!MBusInStationForward.isempty())
	{
		MBusInStationForward.pop(bebe);

		bus_display(bebe->getnumber(), bebe->getDirection(), bebe->get_passengers(), bebe->get_passenger_arr());

		temp.push(bebe);
	}

	while (!temp.isempty())
	{
		temp.pop(bebe);
		MBusInStationForward.push(bebe);
	}

	while (!MBusInStationBackward.isempty())
	{
		MBusInStationBackward.pop(bebe);
		bus_display(bebe->getnumber(), bebe->getDirection(), bebe->get_passengers(), bebe->get_passenger_arr());

		temp.push(bebe);
	}

	while (!temp.isempty())
	{
		temp.pop(bebe);
		MBusInStationBackward.push(bebe);
	}

	while (!WBusInStationForward.isempty())
	{
		WBusInStationForward.pop(bebe);
		bus_display(bebe->getnumber(), bebe->getDirection(), bebe->get_passengers(), bebe->get_passenger_arr());

		temp.push(bebe);
	}

	while (!temp.isempty())
	{
		temp.pop(bebe);
		WBusInStationForward.push(bebe);
	}

	while (!WBusInStationBackward.isempty())
	{
		WBusInStationBackward.pop(bebe);
		bus_display(bebe->getnumber(), bebe->getDirection(), bebe->get_passengers(), bebe->get_passenger_arr());

		temp.push(bebe);
	}

	while (!temp.isempty())
	{
		temp.pop(bebe);
		WBusInStationBackward.push(bebe);
	}
}

void UI::Print_error()
{
	Print("error cannot open file");
}

void UI::display_stations_and_finished_queue(int stationNum, fifoqueue<Passenger*> finished_queue,Station** stationList, int time)
{

	Print("time [");
	Print(time / 60);
	Print(":");
	Print(time % 60);
	Print("]\n");

	for (int i = 1; i < stationNum; i++)
	{
		stationList[i]->displayinfo();

	}
	Print("-----------------------------------------------------------------------------------\n2) Busses in Check up: ");
	stationList[0]->displaycheckup();
	Print("-----------------------------------------------------------------------------------\n3) finished Passeners: ");
	finished_queue.print();
}

void UI::getchar()
{
	Print("\npress any key to continue...");

}
void UI::silent_mode()
{
	Print("Silent Mode\nsimulation starts....\n");
}
void UI::simulation_ends()
{
	Print("Simulation ends, output file created");
}

