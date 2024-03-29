#include "Station.h"
#include<iostream>
#include<string>
using namespace std;

int Station:: travel_distance = 0;
int Station::station_count = 0;
int Station::boardTime = 0;

void Station::setstationcount(int count)
{
	station_count = count;
}

Station::Station(int num):number(num)
{
}

bool Station::exitpassenger(int id)
{
	Passenger* temp = new Passenger("NP", id);
	if (stationpassengersForward.remove(temp))
		return true;
	if (stationpassengersBackward.remove(temp))
		return true;
	if (WheelChairQForward.remove(temp))
		return true;
	if (WheelChairQBackward.remove(temp))
		return true;
	return false;
}

void Station::exitpassengerbytype(Passenger*& leaving, int type)
{
	bool stop = false;
	fifoqueue<Passenger*> tempQ;
	Passenger* moved = nullptr;

	if (type != 10)
	{
		while (!stationpassengersForward.isempty())
		{
			stationpassengersForward.pop(moved);
			if (!stop && moved->GetPassengerPriority() == type)
			{
				leaving = moved;
				stop = true;
			}
			else
				tempQ.push(moved);
		}
		while (!tempQ.isempty())
		{
			tempQ.pop(moved);
			stationpassengersForward.push(moved, moved->GetPassengerPriority());
		}

		if (stop)
			return;

		while (!stationpassengersBackward.isempty())
		{
			stationpassengersBackward.pop(moved);
			if (!stop && moved->GetPassengerPriority() == type)
			{
				leaving = moved;
				stop = true;
			}
			else
				tempQ.push(moved);
		}
		while (!tempQ.isempty())
		{
			tempQ.pop(moved);
			stationpassengersBackward.push(moved, moved->GetPassengerPriority());
		}

		if (stop)
			return;
	}

	else
	{
		while (!WheelChairQForward.isempty())
		{
			WheelChairQForward.pop(moved);
			if (!stop && moved->GetPassengerPriority() == type)
			{
				leaving = moved;
				stop = true;
			}
			else
				tempQ.push(moved);
		}
		while (!tempQ.isempty())
		{
			tempQ.pop(moved);
			WheelChairQForward.push(moved);
		}

		if (stop)
			return;

		while (!WheelChairQBackward.isempty())
		{
			WheelChairQBackward.pop(moved);
			if (!stop && moved->GetPassengerPriority() == type)
			{
				leaving = moved;
				stop = true;
			}
			else
				tempQ.push(moved);
		}
		while (!tempQ.isempty())
		{
			tempQ.pop(moved);
			WheelChairQBackward.push(moved);
		}

		if (stop)
			return;

	}

}

void Station::displayinfo()
{
	printer.Print("==============Station#" + to_string(number)+"=================\n");

	printer.Print(stationpassengersForward.sizebypri(3)+ stationpassengersForward.sizebypri(2)+ stationpassengersForward.sizebypri(1)+ stationpassengersBackward.sizebypri(3) + stationpassengersBackward.sizebypri(2) + stationpassengersBackward.sizebypri(1));

	printer.Print("  Waiting SP: FWD[");

	if (stationpassengersForward.PrintByPriority(3))
		printer.Print("(AG) , ");
	if (stationpassengersForward.PrintByPriority(2))
		printer.Print("(PD) , ");
	if (stationpassengersForward.PrintByPriority(1))
		printer.Print("(PW)");

	printer.Print("]  BCK[");

	if (stationpassengersBackward.PrintByPriority(3))
		printer.Print("(AG) , ");
	if (stationpassengersBackward.PrintByPriority(2))
		printer.Print("(PD) , ");
	if (stationpassengersBackward.PrintByPriority(1))
		printer.Print("(PW)");

	printer.Print("]\n");

	printer.Print(stationpassengersForward.sizebypri(0)+ stationpassengersBackward.sizebypri(0));

	printer.Print("  Waiting NP: FWD[");

	stationpassengersForward.PrintByPriority(0);

	printer.Print("]  BCK[");

	stationpassengersBackward.PrintByPriority(0);

	printer.Print("]\n");

	printer.Print(WheelChairQBackward.sizebypri(10) + WheelChairQForward.sizebypri(10));

	printer.Print("  Waiting WP: FWD[");

	WheelChairQForward.PrintByPriority(10);

	printer.Print("]  BCK[");

	WheelChairQBackward.PrintByPriority(10);

	printer.Print("]\n");

	int total = MBusInStationForward.size() + MBusInStationBackward.size() + WBusInStationForward.size() + WBusInStationBackward.size();
	printer.Print(to_string(total) + " in this station:\n");
	fifoqueue<Bus*> temp;
	Bus* bebe;
	while (!MBusInStationForward.isempty())
	{
		MBusInStationForward.pop(bebe);
		bebe->display();
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
		bebe->display();
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
		bebe->display();
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
		bebe->display();
		temp.push(bebe);
	}

	while (!temp.isempty())
	{
		temp.pop(bebe);
		WBusInStationBackward.push(bebe);
	}
	
}

void Station::displaycheckup()
{
	if (number != 0)
		return;

	fifoqueue<Bus*> temp;
	Bus* bebe;
	while (!MBusInStationForward.isempty())
	{
		MBusInStationForward.pop(bebe);
		if(bebe->getmaintain())
		printer.Print(to_string(bebe->getnumber())+", ");
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
		printer.Print(to_string(bebe->getnumber()) + ", ");
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
		printer.Print(to_string(bebe->getnumber()) + ", ");	
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
		printer.Print(to_string(bebe->getnumber()) + ", ");	
		temp.push(bebe);
	}

	while (!temp.isempty())
	{
		temp.pop(bebe);
		WBusInStationBackward.push(bebe);
	}
	printer.Print("\n");
}

void Station::insertpassenger(Passenger* incoming)
{
	if (incoming->getdirection())
	{
		if (incoming->GetPassengerPriority() == 10)
			WheelChairQForward.push(incoming);
		else
			stationpassengersForward.push(incoming, incoming->GetPassengerPriority());
	}
	else
	{
		if (incoming->GetPassengerPriority() == 10)
			WheelChairQBackward.push(incoming);
		else
			stationpassengersBackward.push(incoming, incoming->GetPassengerPriority());
	}
}

void Station::EnqueueBus(Bus* incoming, int curr_time)
{
	if (number == 0)
	{
		incoming->setfixtime(curr_time);
	}

	if (incoming->isempty() && incoming->getmaintain() && number != 0)
	{
		incoming->setArriveTime(curr_time + incoming->gettimebetweenstations());
		incoming->upgrade_station(station_count, curr_time);
		return;
	}

	if (incoming->getDirection())
	{
		if (incoming->getBusType())
		{
			MBusInStationForward.push(incoming);
		}
		else
		{
			WBusInStationForward.push(incoming);
		}
	}
	else
	{
		if (incoming->getBusType())
		{
			MBusInStationBackward.push(incoming);
		}
		else
		{
			WBusInStationBackward.push(incoming);
		}
	}
	incoming->set_station(number);
	incoming->setInStation(true);
	incoming->setemptying(false);

}

void Station::refreshstation(fifoqueue<Passenger*> &finished_queue,int curr_time)     //does the usual operations in a station 
{
	int perminute = 60 / boardTime;

	if (!MBusInStationForward.isempty())
	{
		if (MBusInStationForward.peek()->exit_passenger(finished_queue, perminute,curr_time))
			MBusInStationForward.peek()->setemptying(true);

		for (int i = 0; i < perminute; i++)
		{
			if (MBusInStationForward.peek()->is_full() || stationpassengersForward.isempty() || !MBusInStationForward.peek()->isdoneemptying() || MBusInStationForward.peek()->getmaintain())
				break;

			Passenger* psg;

			stationpassengersForward.pop(psg);

			MBusInStationForward.peek()->enter_passenger(psg,curr_time);

		}
	}

	if (!MBusInStationBackward.isempty())
	{
		if (MBusInStationBackward.peek()->exit_passenger(finished_queue, perminute,curr_time))
			MBusInStationBackward.peek()->setemptying(true);

		for (int i = 0; i < perminute; i++)
		{
			if (MBusInStationBackward.peek()->is_full() || stationpassengersBackward.isempty() || !MBusInStationBackward.peek()->isdoneemptying() || MBusInStationBackward.peek()->getmaintain())
				break;

			Passenger* psg;

			stationpassengersBackward.pop(psg);

			MBusInStationBackward.peek()->enter_passenger(psg,curr_time);

		}
	}
	
	if (!WBusInStationForward.isempty())
	{ 
		if (WBusInStationForward.peek()->exit_passenger(finished_queue, perminute,curr_time))
			WBusInStationForward.peek()->setemptying(true);

		for (int i = 0; i < perminute; i++)
		{
			if (WBusInStationForward.peek()->is_full() || WheelChairQForward.isempty() || !WBusInStationForward.peek()->isdoneemptying() || WBusInStationForward.peek()->getmaintain())
				break;

			Passenger* psg;

			WheelChairQForward.pop(psg);

			WBusInStationForward.peek()->enter_passenger(psg,curr_time);

		}
	}

	if (!WBusInStationBackward.isempty())
	{
		if (WBusInStationBackward.peek()->exit_passenger(finished_queue, perminute,curr_time))
			WBusInStationBackward.peek()->setemptying(true);

		for (int i = 0; i < perminute; i++)
		{
			if (WBusInStationBackward.peek()->is_full() || WheelChairQBackward.isempty() || !WBusInStationBackward.peek()->isdoneemptying() || WBusInStationBackward.peek()->getmaintain())
				break;

			Passenger* psg;

			WheelChairQBackward.pop(psg);

			WBusInStationBackward.peek()->enter_passenger(psg,curr_time);
		}
	}
}

void Station::DequeueBus(int curr_time)
{
	Bus* Mbus = nullptr;
	if (!MBusInStationForward.isempty())
	{
		if ((number==0 && MBusInStationForward.peek()->getfixtime() == curr_time) || ((MBusInStationForward.peek()->is_full() || stationpassengersForward.isempty()) && (MBusInStationForward.peek()->isdoneemptying() && number !=0)))
		{
			MBusInStationForward.peek()->setInStation(false);
			MBusInStationForward.peek()->setArriveTime(travel_distance + curr_time);
			MBusInStationForward.pop(Mbus);
		}
	}
	if (!MBusInStationBackward.isempty())
	{
		if ((number==0 && MBusInStationBackward.peek()->getfixtime() == curr_time) || ((MBusInStationBackward.peek()->is_full() || stationpassengersBackward.isempty()) && (MBusInStationBackward.peek()->isdoneemptying() && number != 0)))
		{
			MBusInStationBackward.peek()->setInStation(false);
			MBusInStationBackward.peek()->setArriveTime(travel_distance + curr_time);
			MBusInStationBackward.pop(Mbus);
		}
	}
	if (!WBusInStationForward.isempty())
	{
		if ((number == 0 && WBusInStationForward.peek()->getfixtime() == curr_time) || ((WBusInStationForward.peek()->is_full() || WheelChairQForward.isempty()) && (WBusInStationForward.peek()->isdoneemptying() && number !=0)))
		{
			WBusInStationForward.peek()->setInStation(false);
			WBusInStationForward.peek()->setArriveTime(travel_distance + curr_time);
			WBusInStationForward.pop(Mbus);
		}
	}
	if (!WBusInStationBackward.isempty())
	{
		if ((number ==0 && WBusInStationBackward.peek()->getfixtime() == curr_time) || ((WBusInStationBackward.peek()->is_full() || WheelChairQBackward.isempty()) && (WBusInStationBackward.peek()->isdoneemptying() && number !=0)))
		{
			WBusInStationBackward.peek()->setInStation(false);
			WBusInStationBackward.peek()->setArriveTime(travel_distance + curr_time);
			WBusInStationBackward.pop(Mbus);
		}
	}

	if (Mbus != nullptr)
	{
		if (number == 0)
		{
			Mbus->resetcurrtrips();
			Mbus->setmaintain(false);
		}
		Mbus->upgrade_station(station_count,curr_time);
	}
}

void Station::setTravelDistance(int dist)
{
	travel_distance = dist;
}

//mahmoud phase 2
void Station::clear_passengers()
{
	Passenger* temp;

	while (!stationpassengersForward.isempty())
	{
		stationpassengersForward.pop(temp);
	}
	while (!stationpassengersBackward.isempty())
	{
		stationpassengersBackward.pop(temp);
	}
	while (!WheelChairQForward.isempty())
	{
		WheelChairQForward.pop(temp);
	}
	while (!WheelChairQBackward.isempty())
	{
		WheelChairQBackward.pop(temp);
	}

}
//mahmoud phase 2


void Station::setboardtime(int time)
{
	boardTime = time;
}

void Station::promotePassengers(int curr_time)
{
	fifoqueue<Passenger*> notpromotedQ;
	fifoqueue<Passenger*> promotedQ;
	Passenger* temp;

	while (!stationpassengersForward.isempty())
	{
		stationpassengersForward.pop(temp);
		if (curr_time - temp->getarrivetime() == temp->getmaxwait() && temp->GetPassengerPriority() == 0)
		{
			temp->setpromoted(true);
			temp->UpgradePriority();
			promotedQ.push(temp);
		}
		else
			notpromotedQ.push(temp);
	}

	while (!promotedQ.isempty())
	{
		promotedQ.pop(temp);
		stationpassengersForward.push(temp, temp->GetPassengerPriority());
	}

	while (!notpromotedQ.isempty())
	{
		notpromotedQ.pop(temp);
		stationpassengersForward.push(temp, temp->GetPassengerPriority());
	}

	while (!stationpassengersBackward.isempty())
	{
		stationpassengersBackward.pop(temp);
		if (curr_time - temp->getarrivetime() == temp->getmaxwait() && temp->GetPassengerPriority() == 0)
		{
			temp->setpromoted(true);
			temp->UpgradePriority();
			promotedQ.push(temp);
		}
		else
			notpromotedQ.push(temp);
	}

	while (!promotedQ.isempty())
	{
		promotedQ.pop(temp);
		stationpassengersBackward.push(temp, temp->GetPassengerPriority());
	}

	while (!notpromotedQ.isempty())
	{
		notpromotedQ.pop(temp);
		stationpassengersBackward.push(temp, temp->GetPassengerPriority());
	}
}

Passenger* Station::get_random_passenger(int number)
{
	// (1) Move one SP passenger to the Finish list
	if (number >= 1 && number <= 25)
	{
		if (!stationpassengersForward.isempty())
		{
			while (!stationpassengersForward.isempty())
			{
				fifoqueue<Passenger*> tempQ;
				Passenger* p;
				if (stationpassengersForward.peek()->GetPassengerPriority() >= 1 || stationpassengersForward.peek()->GetPassengerPriority() <= 3)
				{
					Passenger* p;
					stationpassengersForward.pop(p);
					while (!tempQ.isempty())
					{
						tempQ.push(p);
						stationpassengersForward.pop(p);
					}
					return p;
				}
				stationpassengersForward.pop(p);
				tempQ.push(p);
			}
		}

		else if (!stationpassengersBackward.isempty())
		{

			while (!stationpassengersBackward.isempty())
			{
				fifoqueue<Passenger*> tempQ;
				Passenger* p;
				if (stationpassengersBackward.peek()->GetPassengerPriority() >= 1 || stationpassengersBackward.peek()->GetPassengerPriority() <= 3)
				{
					Passenger* p;
					stationpassengersBackward.pop(p);
					while (!tempQ.isempty())
					{
						tempQ.push(p);
						stationpassengersBackward.pop(p);
					}
					return p;
				}
				stationpassengersBackward.pop(p);
				tempQ.push(p);
			}
		}
	}

	// (2) Move one WP passenger to the Finish list
	else if (number >= 35 && number <= 45)
	{
		if (!WheelChairQForward.isempty())
		{
			Passenger* p;
			WheelChairQForward.pop(p);
			return p;
		}

		else if (!WheelChairQBackward.isempty())
		{

			Passenger* p;
			WheelChairQBackward.pop(p);
			return p;
		}
	}

	// (3) Move one NP passenger to the Finish list
	else if (number >= 50 && number <= 60)
	{
		if (!stationpassengersForward.isempty())
		{
			while (!stationpassengersForward.isempty())
			{
				fifoqueue<Passenger*> tempQ;
				Passenger* p;
				if (stationpassengersForward.peek()->GetPassengerPriority() == 0)
				{
					stationpassengersForward.pop(p);
					while (!tempQ.isempty())
					{
						tempQ.push(p);
						stationpassengersForward.pop(p);
					}
					return p;
				}
				stationpassengersForward.pop(p);
				tempQ.push(p);
			}
		}

		else if (!stationpassengersBackward.isempty())
		{

			while (!stationpassengersBackward.isempty())
			{
				fifoqueue<Passenger*> tempQ;
				Passenger* p;
				if (stationpassengersBackward.peek()->GetPassengerPriority() == 0)
				{
					stationpassengersBackward.pop(p);
					while (!tempQ.isempty())
					{
						tempQ.push(p);
						stationpassengersBackward.pop(p);
					}
					return p;
				}
				stationpassengersBackward.pop(p);
				tempQ.push(p);
			}
		}
	}

	return nullptr;
}


Station::~Station()
{
}
