
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

	if (time<=(240)+15*count_busses)
	{
		if(time%15==0)
		{
			stationList[0]->DequeueBus(time);
		}
	}

	if (time <= 22 * 60)
	{
		for (int i = 0; i < count_busses; i++)
		{
			if (!Busses_arr[i]->isempty())
			{
				Busses_arr[i]->plusbusytime();
				Busses_arr[i]->setutilization();
			}
			if (!Busses_arr[i]->IsInStation())
			{
				if (time == Busses_arr[i]->getArriveTime())
				{
					stationList[Busses_arr[i]->get_station()]->EnqueueBus(Busses_arr[i],time);
				}
			}
		}
	}

	else if (time > 22 * 60)
	{
		for (int i = 0; i < count_busses; i++)
		{
			if (!Busses_arr[i]->isempty())
			{
				Busses_arr[i]->plusbusytime();
				Busses_arr[i]->setutilization();
			}
			if (Busses_arr[i]->isempty() && !Busses_arr[i]->getoffhoursmode())
			{
				Busses_arr[i]->setoffhoursmode(time);
			}

			if (time == Busses_arr[i]->getArriveTime())
			{
				stationList[0]->EnqueueBus(Busses_arr[i],time);
			}
		}
	}
}

void Company::updatestations()
{

	for (int i = 0; i < stationNum; i++)
	{
		stationList[i]->promotePassengers(time);
		stationList[i]->refreshstation(finished_queue,time);
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

	reader >> stations >> distance >> mbus >> wbus >> mbuscap >> wbuscap >> journies >> mbusfix >> wbusfix >> maxwait>> geton; // reading initial values in order
	
	stationList = new Station*[stations+1];  stationNum = stations+1;  //setting array for stations
	
	for (int i = 0; i < stations+1; i++)   //loop for creating stations
	{
		stationList[i] = new Station(i);
	}
	stationList[0]->setTravelDistance(distance); stationList[0]->setstationcount(stations); stationList[0]->setboardtime(geton);

	Busses_arr = new Bus * [wbus + mbus]; count_busses = wbus + mbus;   //setting array of busses
	count_Mbus = mbus; count_wbus = wbus;

	bool turn = true;
	int gap= abs(mbus-wbus);
	int index = 0;

	int pls = 240;
	for (int i = 0; i < count_busses - gap; i++)  //loop for creating busses
	{
		if (turn)
		{
			Busses_arr[i] = new Bus(mbuscap, 0, 'M', i + 1);
			stationList[0]->EnqueueBus(Busses_arr[i], time);
			Busses_arr[i]->setmaintenancetime(mbusfix);
			turn = false;
		}
		else
		{
			Busses_arr[i] = new Bus(wbuscap, 0, 'W', i + 1);
			stationList[0]->EnqueueBus(Busses_arr[i], time);
			Busses_arr[i]->setmaintenancetime(wbusfix);
			turn = true;
		}
		index++;
		Busses_arr[i]->initializefixtime(pls);
		pls += 15;
	}

	for(int i=index ; i<count_busses;i++)
	{
		if (mbus > wbus)
		{
			Busses_arr[i] = new Bus(mbuscap, 0, 'M', i + 1);
			stationList[0]->EnqueueBus(Busses_arr[i], time);
			Busses_arr[i]->setmaintenancetime(mbusfix);
		}

		else if (wbus > mbus)
		{
			Busses_arr[i] = new Bus(wbuscap, 0, 'W', i + 1);
			stationList[0]->EnqueueBus(Busses_arr[i], time);
			Busses_arr[i]->setmaintenancetime(wbusfix);
		}

		Busses_arr[i]->initializefixtime(pls);
		pls += 15;
	}

	Busses_arr[0]->SetTimeBetweenStations(distance);  Busses_arr[0]->SetMaxStations(journies);   capacityM = mbuscap;  capacityW = wbuscap;

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

void Company::writeFile()
{
	ofstream writer("output_file.txt");
	writer << "FT\t\t" << "ID\t\t" << "AT\t\t" << "WT\t\t" << "TT" << endl;
	Passenger* temp;
	int totalsize = finished_queue.size();
	int sizeNP = 0;
	int sizeSP = 0;
	int sizeWP = 0;
	int totalwait = 0;
	int totaltrip = 0;
	int totalpromoted = 0;
	int totalbusybus = 0;
	float totalutilizationM = 0.0;
	float totalutilizationW = 0.0;
	while (!finished_queue.isempty())
	{
		finished_queue.pop(temp);
		totalwait += (temp->getmovetime() - temp->getarrivetime());
		totaltrip += (temp->getfinishtime() - temp->getmovetime());
		if (temp->getpromoted())
			totalpromoted++;
		if (temp->GetPassengerPriority() == 0)
			sizeNP++;
		if (temp->GetPassengerPriority() == 10)
			sizeWP++;
		if (temp->GetPassengerPriority() == 1 || temp->GetPassengerPriority() == 2 || temp->GetPassengerPriority() == 3)
			sizeSP++;

		writer << temp->getfinishtime()/60<<":"<<temp->getfinishtime()%60 << "\t\t" << temp->getPassengerID() << "\t\t" << temp->getarrivetime()/60 <<":"<< temp->getarrivetime()%60
			<<"\t\t" << (temp->getmovetime() - temp->getarrivetime())/60 <<":"<<(temp->getfinishtime() - temp->getarrivetime()) % 60 <<"\t\t"
			<< (temp->getfinishtime() - temp->getmovetime())/60 <<":"<< (temp->getfinishtime() - temp->getmovetime()) % 60 << endl;
	}

	writer << "Passengers: " << totalsize <<"[NP: "<<sizeNP<<", SP: "<<sizeSP<<", WP: "<<sizeWP<<"]"<<endl;
	writer << "Passenger avg wait time = " << totalwait / totalsize / 60 << ":" << totalwait / totalsize % 60 << endl;
	writer << "Passenger avg trip time = " << totaltrip / totalsize / 60 << ":" << totaltrip / totalsize % 60 << endl;
	writer << "Auto-promoted Passengers: " << int(float(totalpromoted) / totalsize * 100) << "%" << endl;
	writer << "Busses: " << count_busses << " [WBus: " << count_wbus << ", MBus: " << count_Mbus <<"]" << endl;

	for (int i = 0; i < count_busses; i++)
	{
		totalbusybus += Busses_arr[i]->getbusytime();
		if (Busses_arr[i]->getBusType())
			totalutilizationM += Busses_arr[i]->getutilization();
		else
		    totalutilizationW += Busses_arr[i]->getutilization();
	}
	totalbusybus = totalbusybus / count_busses;

	float actualutilization = ((totalutilizationM / capacityM) + (totalutilizationW / capacityW)) / 2;
	writer << "Avg busy time = " << int(float(totalbusybus) / (20 * 60) * 100) << "%" << endl;
	writer << "Avg utilization = " << actualutilization/ 100 << "%" << endl;

}

bool Company::takeinpassenger()
{
	if (simevents.isempty())
		return false;

}

void Company::simulation()
{
	if (printer.getsim() == 1)
	{
		time = 240;
		while (time <= 24 * 60)
		{
			executeevent();
			updatebusses();
			updatestations();
			display();
			printer.Print("\npress any key to continue...");
			getchar();
			time++;
		}
	}
	else
	{
		printer.Print("Silent Mode\nsimulation starts....\n");
		while (time <= 24 * 60)
		{
			executeevent();
			updatebusses();
			updatestations();
			time++;
		}
	}
	writeFile();
	printer.Print("\nSimulation ends, output file created");
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
	
	printer.Print("time [");
	printer.Print(time / 60);
	printer.Print(":");
	printer.Print(time % 60);
	printer.Print("]\n");

	for (int i = 1; i < stationNum; i++)
	{
		stationList[i]->displayinfo();

	}
	printer.Print("-----------------------------------------------------------------------------------\n2) Busses in Check up: ");
	stationList[0]->displaycheckup();
	printer.Print("-----------------------------------------------------------------------------------\n3) finished Passeners: ");
	finished_queue.print();
}

Company::~Company()
{
}
