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
	checkup_time = 0;
}

Bus::~Bus()
{
	delete[] passenger_arr;
}

void Bus::setemptying(bool done)
{
	doneemptying = done;
}

bool Bus::isdoneemptying()
{
	return doneemptying;
}

void Bus::display()
{
	printer.Print("bus #" + to_string(number) + "\t");
	printer.Print("direction: " + to_string(direction) +"\t");
	if (InStation)
		printer.Print("station: " + to_string(station) + "\t");
	else
		printer.Print("not in station\t");
	printer.Print("number of passengers in bus: " + to_string(num_of_passengers)+"\n");
}

void Bus::upgrade_trips()
{
	if (maintenance_time())
	{
		curr_trips = 0;
	}
	else
	{
		curr_trips++;
	}
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
	upgrade_trips();

	if (maintenance_time())
	{
		set_station(0);
		set_direction(true);// going back to station 0 and direction will be true after maintenance duration
		
		setArriveTime(getTimeBetweenStations() * get_station() + time);//ArriveTime = #stations * time needed for each station + current time
		
		return;
	}

	if (direction == true)
	{
		if (station == size)
		{
			direction = false;
			station--;
		}
		else
			station++;
	}

	else
	{
		if (station == 1)
		{
			direction = true;
		}
		station--;
	}
	setArriveTime(time + getTimeBetweenStations());

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

bool Bus::maintenance_done(int time)
{
	if(checkup_time == time)
		return true;

	checkup_time++;
	return false;
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

int Bus::getTimeBetweenStations()
{
	return TimeBetweenStations;
}

bool Bus::SetTimeBetweenStations(int t)
{
	TimeBetweenStations = t;
	return true;
}

bool Bus::SetMaxStations(int s)
{
	max_trips = s;
	return false;
}
