#include "Company.h"
#include <random>
using namespace std;


void Company::executeevent()
{
	if(!simevents.isempty())
	{
		while (simevents.peek()->gettime() == time)
		{
			Event* event;
			simevents.pop(event);

			event->execute(stationList);

			if (simevents.isempty())
			{
				break;
			}
		}
	}
}

Company::Company()
{
	time = 0; 
}

void Company::updatebusses()
{
	if (time == 0)
	{
		for (int i = 0; i < count_busses; i++)
		{
			stationList[0]->EnqueueBus(Busses_arr[i], finished_queue);
		}
	}

	if (time<=15*count_busses)
	{
		if(time%15==0)
		{
			stationList[0]->DequeueBus(time);
		}
	}

	for (int i = 0; i < count_busses; i++)
	{
		if (!Busses_arr[i]->IsInStation())
		{
			if (time == Busses_arr[i]->getArriveTime())
			{
				stationList[Busses_arr[i]->get_station()]->EnqueueBus(Busses_arr[i], finished_queue);
			}
		}
		
	}
	for (int i = 1; i < stationNum; i++)
	{
		//stationList[i]->promotePassengers(time);
		stationList[i]->DequeueBus(time);
	}
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
	
	stationList = new Station*[stations+1];  stationNum = stations+1;  //setting array for stations
	
	for (int i = 0; i < stations+1; i++)   //loop for creating stations
	{
		stationList[i] = new Station(i);
	}
	stationList[0]->setTravelDistance(distance); stationList[0]->setstationcount(stations);

	Busses_arr = new Bus * [wbus + mbus]; count_busses = wbus + mbus;   //setting array of busses

	for (int i = 0; i < count_busses; i++)  //loop for creating busses
	{
		if (i < mbus)
			Busses_arr[i] = new Bus(mbuscap, 0, 'M');
		else
			Busses_arr[i] = new Bus(wbuscap, 0, 'W');
	}
	Busses_arr[0]->SetTimeBetweenStations(distance);  Busses_arr[0]->SetMaxStations(journies);

	Passenger::setmaxwait(maxwait);  Passenger::setgetontime(geton);

	cout << stations <<" "<< distance <<" "<< wbus <<" "<< mbus <<" "<< wbuscap <<" "<< mbuscap <<" "<< journies <<" "<< wbusfix <<" "<< mbusfix<<endl;  //printing read info for testing
	
	int lines;
	reader >> lines;
	Event* incomingevent;
	for(int i=0;i<lines;i++)  //loop until file ends
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
			((ArrivalEvent*)incomingevent)->setdata(Ptype,disability,fromstation,tostation);
			incomingevent->display();  //for testing

			simevents.push(incomingevent);  //pushes event into queue of events

			//cout << Ptype << " "<< time << " " << ID << " " << fromstation << " " << tostation << " " << disability << endl;  //for testing
		}
		else if (type == 'L')  // if event is leave
		{
			int arrtime, ID; char trash;

			reader >> arrtime >> trash;  //same as arrival reads info of leaveevent

			int time = arrtime * 60;
			int leavestation;
			reader >> arrtime >> ID>>leavestation;

			time += arrtime;

			incomingevent = new LeaveEvent(time,ID, 'L'); //create leaveevent
			((LeaveEvent*)incomingevent)->setstation(leavestation);
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


void Company::simulation()
{
	while (time<=24*60)
	{
		executeevent();
		updatebusses();
		time++;
	}
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

	finished_queue.print();
}

void Company::simulation_phase_1()
{
	while (time <= 24 * 60)
	{
		executeevent();
		move_to_finished_queue();
		//display_finished_queue();
		cout << endl << endl << "-------------------------------------------------------------------";
		time++;
	}
}

int Company::generate_ramdom()
{
	// Seed the random number generator with a random device
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(1, 100);

	// Generate a random number between 1 and 100
	return dis(gen);
}

void Company::move_to_finished_queue()
{
	for (int i = 0; i < stationNum; i++)
	{
		//create a random number for each station:
		int randomNumber = generate_ramdom();

		// get a passenger 
		Passenger* p = stationList[i]->get_random_passenger(randomNumber);

		//if nullptr (there are no passengers in the stationList)
		if (!p) continue;

		else
		{
			finished_queue.push(p);

			//display the passenger we got
			cout << "\nfor a Random Number " << randomNumber << ":\nPassenger we got is:\n";
			p->display();
		}
	}
}

void Company::display_finished_queue()
{
	fifoqueue<Passenger*> tempQ;
	Passenger* p;

	while (!finished_queue.isempty())
	{
		finished_queue.pop(p);
		tempQ.push(p);
		p->display();
	}

	while (!tempQ.isempty())
	{
		tempQ.pop(p);
		finished_queue.push(p);
	}
}



Company::~Company()
{
}
