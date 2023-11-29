#include "Company.h"
#include"Station.h"

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

Company::~Company()
{
}
