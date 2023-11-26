#include "Bus.h"

Bus::Bus(int size, int max, int bus_num, int s, char type)
	: BC(size), max_trips(max), bus_number(bus_num),station(s)
{
	passenger_arr = new Passenger * [size];
	finished_queue = new fifoqueue<Passenger*>();
	//arrivalEvent = new ArrivalEvent;
	//leaveEvent = new LeaveEvent;

	curr_trips = 0;
	num_of_passengers = 0;
	direction = 1;
	direction = true;
	closed = false;
	if (type == 'W')
		bus_type = 0;
	else
		bus_type = 1;
}

Bus::~Bus()
{
	delete[] passenger_arr;
	delete finished_queue;
	delete arrivalEvent;
	delete leaveEvent;

}

void Bus::display_bus()
{
	string available = "No, not available", mixed = "No, not mixed bus";
	if (is_available())
		available = "Yes";
	if (is_mixed_bus())
		mixed = "Yes, mixed bus";

	cout << "Reading Bus Data: "<< endl
		<< "Station Number: " << get_station() << endl
		<< "Number of Passengers: " << get_passengers()<< endl
		<< "Is available?: " << available << endl
		<< "Station Number: " << mixed << endl
		<< "Station Number: " << maintenance_time() << endl;
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
	if(bus_type == 'M')
		return true;
	return false;
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

void Bus::set_arrival_event(ArrivalEvent * arrivalEvt)
{
	arrivalEvent = arrivalEvt;
}

void Bus::set_leave_event(LeaveEvent* leaveEvt)
{
	leaveEvent = leaveEvt;
}

void Bus::arrive_at_station()
{
	// Call the Company's method to handle the arrival
	//company->handle_bus_arrival(this);

	// Trigger the arrival event
	//arrivalEvent->trigger();

}

void Bus::leave_station()
{
	// Call the Company's method to handle the departure
	//company->handle_bus_departure(this);

	// Trigger the leave event
	//leaveEvent->trigger();
}
