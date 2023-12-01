#include "Company.h"


Company::Company()
{
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

	int stations, distance;
	int wbus, mbus, wbuscap, mbuscap;   //defining varaibles to read data into
	int journies, wbusfix, mbusfix;
	int maxwait, geton;

	reader >> stations >> distance >> wbus >> mbus >> wbuscap >> mbuscap >> journies >> wbusfix >> mbusfix >>maxwait>>geton; // reading initial values in order
	
	stationList = new Station*[stations];  stationNum = stations;  //setting array for stations
	
	for (int i = 0; i < stations; i++)   //loop for creating stations
	{
		stationList[i] = new Station(i);
	}
	stationList[0]->setTravelDistance(distance);

	Busses_arr = new Bus * [wbus + mbus]; count_busses = wbus + mbus;   //setting array of busses

	for (int i = 0; i < count_busses; i++)  //loop for creating busses
	{
		if (i < mbus)
			Busses_arr[i] = new Bus(mbuscap, 0, 'M');
		else
			Busses_arr[i] = new Bus(wbuscap, 0, 'W');
	}
	Busses_arr[0]->SetTimeBetweenStations(distance);  Busses_arr[0]->SetMaxStations(journies);


	cout << stations <<" "<< distance <<" "<< wbus <<" "<< mbus <<" "<< wbuscap <<" "<< mbuscap <<" "<< journies <<" "<< wbusfix <<" "<< mbusfix<<endl;  //printing read info for testing
	
	Event* incomingevent;
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


			incomingevent = new ArrivalEvent(time,ID, 'A');  //creates an arrivalevent for the passenger with set time

			incomingevent->display();  //for testing

			simevents.push(incomingevent);  //pushes event into queue of events

			//cout << Ptype << " "<< time << " " << ID << " " << fromstation << " " << tostation << " " << disability << endl;  //for testing
		}
		else if (type == 'L')  // if event is leave
		{
			int arrtime, ID; char trash;

			reader >> arrtime >> trash;  //same as arrival reads info of leaveevent

			int time = arrtime * 60;

			reader >> arrtime >> ID;

			time += arrtime;

			incomingevent = new LeaveEvent(time,ID, 'L'); //create leaveevent
			incomingevent->display();  //for testing

			simevents.push(incomingevent);  //pushes into queue of events

			//cout << time << " " << ID << endl;  
		}
		else
			break;
	}

}

bool Company::takeinpassenger()
{
	if (simevents.isempty())
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

void Company::display()
{
	cout << "displaying company info:" << endl <<"population:"<<endl;
	population.print();
	cout << "stations:" << endl;
	for (int i = 0; i < stationNum; i++)
		stationList[i]->displayinfo();
	cout << "busses:" << endl;
	for (int i = 0; i < count_busses; i++)
		Busses_arr[i]->display();
}

Company::~Company()
{
}
