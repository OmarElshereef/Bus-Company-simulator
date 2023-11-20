#include "Bus.h"

Bus::Bus(int size, int max, char type) : BC(size), max_trips(max)
{
	passenger_arr = new Passenger * [size];
	curr_trips = 0;
	num_of_passengers = 0;
	direction = true;
	closed = false;
	if (type == 'W')
		bus_type = 0;
	else
		bus_type = 1;
}

Bus::~Bus()
{
	for (int i = 0; i < BC; i++)
		delete passenger_arr[i];
}

bool Bus::get_door()
{
	return closed; // closed=1 , open=0
}

void Bus::set_door(bool door)
{
	closed = door; // closed=1 , open=0
}

int Bus::get_station()
{
	return station;
}

void Bus::set_station(int s)
{
	station = s;
}

int Bus::get_passengers()
{
	return num_of_passengers;
}

void Bus::set_passengers(int p)
{
	num_of_passengers = p;
}

bool Bus::is_full()
{
	return num_of_passengers == BC;
}

bool Bus::is_available()
{
	return num_of_passengers <= BC;
}

bool Bus::is_mixed_bus()
{
	return bus_type == 'M';
}

bool Bus::maintenance_time()
{
	return max_trips == curr_trips;
}

void Bus::remove(int index)
{
	if (index + 1 == num_of_passengers)
	{
		delete passenger_arr[index];
		num_of_passengers--;
		return;
	}

	for (int i = index + 1; i < num_of_passengers; i++)
	{
		passenger_arr[i] = passenger_arr[i - 1];
	}
	num_of_passengers--;
	return;
}

bool Bus::enter_passenger(Passenger* p)
{
	if (is_available())
	{
		int num = get_passengers();
		passenger_arr[num] = p;
		set_passengers(num + 1);
		return true;
	}
	return false;
}

void Bus::exit_passenger(Passenger* p, Passenger** finished_array, int& size)
{
	int num = get_passengers();
	for (int i = 0; i < num; i++)
	{
		if (passenger_arr[i]->getPassengerID() == p->getPassengerID())
		{
			finished_queue->push(p);
			remove(i);
		}
	}
}
