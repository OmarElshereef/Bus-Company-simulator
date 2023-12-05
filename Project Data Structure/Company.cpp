
#include "Company.h"
#include <cstdio>

bool Company::executeevent()
{
	if (simevents.isempty())
		return false;

	if(!simevents.isempty())
	{
		while (simevents.peek()->gettime() == time)
		{
			Event* currevent;
			simevents.pop(currevent);
			

			if (currevent->execute(stationList) &&dynamic_cast<LeaveEvent*>(currevent) != nullptr )
				lines_read--;
			if (simevents.isempty())
			{
				break;
			}
		}
		return true;
	}
}

Company::Company()
{
	time = 0;
	lines_read = 0;
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
}

void Company::updatestations()
{
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
		printer.Print("error cannot open file"); //if file couldn't be opened print error message then quit
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
			lines_read++;
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
			

			simevents.push(incomingevent);  //pushes event into queue of events

			
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
			

			simevents.push(incomingevent);  //pushes into queue of events

		 
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

void Company::simulate_phase_1()
{
	int rndval;
	time = 240;
	Passenger* isleft=nullptr;
	int type;

	while (time <= 1320)
	{
		type = -1;
		isleft = nullptr;
		if (simevents.isempty() && lines_read == 0)
			return;

		executeevent();

		rndval = int((rand() % 60 + 1));;

		if(rndval >=1 && rndval <=25)
		{
			type = 3;
		}
		else if (rndval >= 35 && rndval <= 45)
		{
			type = 10;
		}
		else if (rndval >= 50 && rndval <= 60)
		{
			type = 0;
		}

		if (type != -1)
		{
			if (type == 3)
			{
				for (int i = 0; i < stationNum; i++)
				{
					stationList[i]->exitpassengerbytype(isleft, type);
					if (isleft)
					{
						if (lines_read!=0)
						{
							lines_read--;
						}
						
						finished_queue.push(isleft);
						break;
					}
				}
				if (isleft == nullptr)
				{
					type--;
					for (int i = 0; i < stationNum; i++)
					{
						stationList[i]->exitpassengerbytype(isleft, type);
						if (isleft)
						{
							if (lines_read != 0)
							{
								lines_read--;
							}
							finished_queue.push(isleft);
							break;
						}
					}
					if (isleft == nullptr)
					{
						type--;
						for (int i = 0; i < stationNum; i++)
						{
							stationList[i]->exitpassengerbytype(isleft, type);
							if (isleft)
							{
								if (lines_read != 0)
								{
									lines_read--;
								}
								finished_queue.push(isleft);
								break;
							}
						}
					}
				}
			}
			else
			{
				for (int i = 0; i < stationNum; i++)
				{
					stationList[i]->exitpassengerbytype(isleft, type);
					if (isleft)
					{
						lines_read--;
						finished_queue.push(isleft);
						break;
					}
				}
			}
			
		}
		printer.Print("time ["); 
		printer.Print(time/60);
		printer.Print(":");
		printer.Print(time%60);
		printer.Print("]\n");

		for (int i = 1; i < stationNum; i++)
		{
			stationList[i]->displayinfo();
		}

		printer.Print("finished queue:\n");
		finished_queue.print();
		printer.Print("\n press any key to continue...");
	
		getchar();
		time++;
	}
	
}

void Company::display()
{
	
	population.print();
	
	for (int i = 0; i < stationNum; i++)
		stationList[i]->displayinfo();
	
	for (int i = 0; i < count_busses; i++)
		Busses_arr[i]->display();

	finished_queue.print();
}

Company::~Company()
{
}
