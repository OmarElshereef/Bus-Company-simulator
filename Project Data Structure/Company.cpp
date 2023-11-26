#include "Company.h"

Company::Company()
{
	create_busses();
	timestep [0] = 4;
	timestep [1] = 0;// timestep in hh:mm = 04:00
					 // company working hours: 4:00 to 22:00
	Busses_arr = new Bus * [mbus+ wbus]; //size of array = m busses + w busses
	count_busses = 0;
}

void Company::readFile()
{
	ifstream reader;
	reader.open("input_file.txt"); //opening file

	if (!reader.is_open())
	{
		cout << "error cannot open file"; //if file couldn't be opened print error message then quit
		return;
	}



	reader >> stations >> distance >> wbus >> mbus >> wbuscap >> mbuscap >> journies >> wbusfix >> mbusfix;
	// reading initial values in order
	cout << stations <<" "<< distance <<" "<< wbus <<" "<< mbus <<" "<< wbuscap <<" "<< mbuscap <<" "<< journies <<" "<< wbusfix <<" "<< mbusfix<<endl;
	
	while (!reader.eof())  //looping until file ends
	{
		char type;
		reader >> type;

		if (type == 'A')
		{
			string Ptype, disability ="";  char trash;
			int arrtime, ID, fromstation, tostation;

			reader >> Ptype >> arrtime >> trash;

			int time = arrtime *60;

			reader >> arrtime >> ID >> fromstation >> tostation;

			time += arrtime;

			if (Ptype == "SP")
				reader >> disability;

			Passenger coming;  //should insert data of passenger here
			population.push(coming);

			ArrivalEvent arrive;
			arrivals.push(arrive);

			cout << Ptype << " "<< time << " " << ID << " " << fromstation << " " << tostation << " " << disability << endl;
		}
		else if (type == 'L')
		{
			int arrtime, ID; char trash;

			reader >> arrtime >> trash;

			int time = arrtime * 60;

			reader >> arrtime >> ID;

			time += arrtime;

			LeaveEvent leave;
			leaves.push(leave);

			cout << time << " " << ID << endl;
		}
	}

}

Company::~Company()
{
}

int Company::get_time()
{
	return timestep[0]*60 + timestep[1];
}

void Company::set_time(int hh, int mm)
{
	timestep[0] = hh;
	timestep[1] = mm;
}
/*
int Company::get_buscap()
{
	return mbuscap;
}

int Company::get_journies()
{
	return journies;
}
*/
void Company::create_busses()
{
	for (int i = 0; i < wbus; i++)
	{
		Bus * bus;
		allBusses->push(bus);
	}
	for (int i = 0; i < mbus; i++)
	{
		Bus * bus;
		allBusses->push(bus);
	}
}

void Company::check_bus_arrival()
{
	for (int i = 0; i < count_busses; i++)
	{

		Busses_arr[i]->exit_passenger();
	}
	
}

void Company::release_bus()
{
	if (count_busses < 100)
	{
		Busses_arr[count_busses] =  allBusses->peek();
		count_busses++;
	}
}

void Company::change_station()
{
	for (int i = 0; i < count_busses; i++)
	{
		if (Busses_arr[i]->get_distance() == distance)
		{
			Busses_arr[i]->upgrade_station();
			Busses_arr[i]->set_distance(0);
			if (Busses_arr[i]->get_station() > stations)
				Busses_arr[i]->set_station(Busses_arr[i]->get_station() % stations);
		}
	}
/*if (Busses_arr[i]->get_distance() == stations_distance)
	{
		allBusses[i].set_distance(0);
		bus get in bus queue in station

	}
	*/
}


void Company::time_up()
{
	if (timestep[1] < 59)
		timestep[1]++;
	else if (timestep[1] == 59)
	{
		timestep[0]++;
		timestep[1] = 0;
	}
	else if (timestep[0] == 23 && timestep[1] == 59) // 23:59
	{
		timestep[0] = 0;
		timestep[1] = 0;
	}
}
