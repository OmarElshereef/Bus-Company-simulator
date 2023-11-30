#include "Company.h"
#include"Station.h"

Company::Company()
{
	create_busses();
	timestep[0] = 4;
	timestep[1] = 0;// timestep in hh:mm = 04:00
	// company working hours: 4:00 to 22:00
	Busses_arr = new Bus * [mbus + wbus]; //size of array = m busses + w busses
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

	//int stations, distance;
	//int wbus, mbus, wbuscap, mbuscap;   //defining varaibles to read data into
	//int journies, wbusfix, mbusfix;
	//int maxwait, geton;

	reader >> stations >> distance >> wbus >> mbus >> wbuscap >> mbuscap >> journies >> wbusfix >> mbusfix >>maxwait>>geton; // reading initial values in order
	
	stationList = new Station*[stations];  stationNum = stations;  //setting array for stations
	
	for (int i = 0; i < stations; i++)
	{
		stationList[i] = new Station(i);
	}
	stationList[0]->setTravelDistance(distance);

	cout << stations <<" "<< distance <<" "<< wbus <<" "<< mbus <<" "<< wbuscap <<" "<< mbuscap <<" "<< journies <<" "<< wbusfix <<" "<< mbusfix<<endl;  //printing read info for testing
	
	while (true)  //loop until file ends
	{
		char type;
		reader >> type;   // read event type character
		if (reader.eof())  //if file ends break
			break;
		
		if (type == 'A')   //if event is arrival
		{
			string Ptype, disability = "";  char trash;
			int arrtime, ID, fromstation, tostation;

			reader >> Ptype >> arrtime >> trash;  //read info pertaining to arrived passenger

			int time = arrtime * 60;   //read time of event

			reader >> arrtime >> ID >> fromstation >> tostation;  //reads rest of data

			time += arrtime;

			if (Ptype == "SP")  //is passenger is SP reads additional type
				reader >> disability;

			Passenger coming(Ptype, ID, fromstation, tostation, disability,time);  //new passenger with said data
			coming.setgetontime(geton); coming.setmaxwait(maxwait);

			coming.displayData();  //for testing
			population.push(coming);  //pushes passenger into the population of simulation

			ArrivalEvent arrive(time,ID, 'A');  //creates an arrivalevent for the passenger with set time
			arrive.display();  //for testing

			arrivals.push(arrive);  //pushes event into queue of events

			//cout << Ptype << " "<< time << " " << ID << " " << fromstation << " " << tostation << " " << disability << endl;  //for testing
		}
		else if (type == 'L')  // if event is leave
		{
			int arrtime, ID; char trash;

			reader >> arrtime >> trash;  //same as arrival reads info of leaveevent

			int time = arrtime * 60;

			reader >> arrtime >> ID;

			time += arrtime;

			LeaveEvent leave(time,ID, 'L'); //create leaveevent
			leave.display();  //for testing

			leaves.push(leave);  //pushes into queue of events

			//cout << time << " " << ID << endl;  
		}
		else
			break;
	}

}

bool Company::takeinpassenger()
{
	if (arrivals.isempty())
		return false;

}

int Company::get_time()
{
	return timestep[0] * 60 + timestep[1];
}

void Company::set_time(int hh, int mm)
{
	timestep[0] = hh;
	timestep[1] = mm;
}

void Company::create_busses()
{
	for (int i = 0; i < wbus; i++) // setting wheelchair busses
	{
		Bus* bus = new Bus(wbuscap, journies, 0, 'W'); // size, max journies, station number, bus type
		Busses_arr[i] = bus;
		count_busses++;
	}
	for (int i = 0; i < mbus; i++) // setting mixedbusses busses
	{
		Bus* bus = new Bus(mbuscap, journies, 0, 'M'); // size, max journies, station number, bus type
		Busses_arr[i] = bus;
		count_busses++;
	}
}


void Company::check_bus_arrival()
{
	for (int i = 0; i < count_busses; i++)
	{

		Busses_arr[i]->exit_passenger();
	}

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

void Company::change_station()
{
	/*
	This function to change station to the current one and the distance  and the direction if changed 
	*/
	for (int i = 0; i < count_busses; i++)
	{
		if (Busses_arr[i]->get_distance() == distance)
		{
			if (Busses_arr[i]->get_station() == stations) //the bus in the last station, it must change the direction! 
			{
				Busses_arr[i]->set_direction(false);  // change directon to backward
			}

			Busses_arr[i]->upgrade_station();
			Busses_arr[i]->set_distance(0); //distance here is the time between the two stations
			
		}
	}

}

Company::~Company()
{
}
