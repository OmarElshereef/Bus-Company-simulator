#include "Bus.h"


int Bus::TimeBetweenStations = 0;
int Bus::max_trips = 0;

Bus::Bus(int capacity, int s, char type, int num)
	: BC(capacity), station(s)
{
	number = num;
	passenger_arr = new Passenger * [capacity];
	curr_trips = 0;
	num_of_passengers = 0;
	direction = true;
	bus_type = type;
	InStation = true;
	doneemptying = true;
	offhours = false;
	busytime = 0;
	utilization = 0;
	maintain = false;
	maintenancetime = 0;
}

Bus::~Bus()
{
	delete[] passenger_arr;
}

void Bus::setemptying(bool done)
{
	doneemptying = done;
}

void Bus::initializefixtime(int f)
{
	fixtime = f;
}

void Bus::setfixtime(int f)
{
	fixtime = f+maintenancetime;
}

int Bus::getfixtime()
{
	return fixtime;
}

bool Bus::isdoneemptying()
{
	return doneemptying;
}

void Bus::setmaintenancetime(int t)
{
	maintenancetime = t;
}

int Bus::getmaintenancetime()
{
	return maintenancetime;
}

void Bus::display()
{
	printer.Print("BUS" + to_string(number) + "[");
	if (direction)
		printer.Print("FWD, ");
	else
		printer.Print("BCK, ");

	printer.Print("] {");
	for (int i=0; i < num_of_passengers-1; i++)
	{
		printer.Print(to_string(passenger_arr[i]->getPassengerID()) + ", ");
	}
	if(num_of_passengers!=0)
	printer.Print(to_string(passenger_arr[num_of_passengers - 1]->getPassengerID()));
	printer.Print("}\n");
}

int Bus::get_station()
{
	return station;
}

void Bus::set_station(int s)
{
	station = s;
}

void Bus::set_direction(bool d) //d=true => forward or d=false => backward
{
	direction = d;
}

void Bus::upgrade_station(int size, int time)
{
	if (direction == true)
	{
		if (station == size)
		{
			setArriveTime(time + 1);
			if (curr_trips == max_trips - 1 && !offhours)
			{
				curr_trips++;
				maintain = true;
			}
			else
				curr_trips++;
			direction = false;

		}
		else
			station++;
	}
	else
	{
		if (station == 1)
		{
			if (maintain)
			{
				direction = true;
				station--;
				return;
			}

			setArriveTime(time + 1);
			if (curr_trips == max_trips && !offhours)
			{
				maintain = true;
				station--;
			}
			else
				curr_trips++;
			direction = true;
		}
		else
		station--;
	}

}

int Bus::get_distance()
{
	return distance;
}

void Bus::set_distance(int d)
{
	distance = d;
}

int Bus::get_passengers()
{
	return num_of_passengers;
}

void Bus::setutilization()
{
	utilization += num_of_passengers;
}

float Bus::getutilization()
{
	return utilization;
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
	return num_of_passengers < BC;
}

bool Bus::is_mixed_bus()
{
	if(bus_type == 'M')
		return true;
	return false;
}

bool Bus::isempty()
{
	return num_of_passengers ==0;
}

bool Bus::maintenance_time()
{
	return max_trips == curr_trips;
}

void Bus::resetcurrtrips()
{
	curr_trips = 0;
}

bool Bus::getmaintain()
{
	return maintain;
}

void Bus::setmaintain(bool m)
{
	maintain = m;
}

void Bus::remove(int index)
{
	passenger_arr[index] = nullptr;

	for (int i = index ; i < num_of_passengers; i++)
	{
		passenger_arr[i] = passenger_arr[i + 1];
	}
	num_of_passengers--;
	return;
}

bool Bus::enter_passenger(Passenger* p, int curr_time)
{
	if (is_available())
	{
		p->setmovetime(curr_time);
		int num = get_passengers();
		passenger_arr[num] = p;
		set_passengers(num + 1);
		return true;
	}
	return false;
}

bool Bus::exit_passenger(fifoqueue<Passenger*> &finished_array, int permin, int curr_time)
{
	bool flag = true;
	int done = 0;
	for (int i = 0; i < num_of_passengers; i++)
	{
		if (done == permin)
			break;

		if (passenger_arr[i]->GetEndStation() == station)
		{
			passenger_arr[i]->setfinishtime(curr_time);
			finished_array.push(passenger_arr[i]);
			remove(i);
			flag = false;
			i--;
			done++;
		}
	}
	return flag;
}

void Bus::setArriveTime(int t)
{
	EstimatedTimeOfArrival = t;
}

int Bus::getArriveTime()
{
	return EstimatedTimeOfArrival;
}

void Bus::setInStation(bool Case)
{
	InStation = Case;
}

void Bus::plusbusytime()
{
	busytime++;
}

int Bus::getbusytime()
{
	return busytime;
}

bool Bus::IsInStation()
{
	return InStation;
}

bool Bus::getDirection()
{
	return direction;
}

bool Bus::getBusType()
{
	if (bus_type=='M')
	{
		return true;
	}
	return false;
}

void Bus::setoffhoursmode(int curr_time)
{
	direction == false;
	setArriveTime(station*TimeBetweenStations+curr_time);
	offhours = true;
}

bool Bus::getoffhoursmode()
{
	return offhours;
}

bool Bus::SetTimeBetweenStations(int t)
{
	TimeBetweenStations = t;
	return true;
}

int Bus::gettimebetweenstations()
{
	return TimeBetweenStations;
}

bool Bus::SetMaxStations(int s)
{
	max_trips = s;
	return false;
}
