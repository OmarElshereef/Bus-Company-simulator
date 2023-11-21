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

	reader >> stations >> distance >> wbus >> mbus >> wbuscap >> mbuscap >> journies >> wbusfix >> mbusfix >>maxwait>>geton;
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

			Passenger coming(Ptype, ID, fromstation, tostation, disability);  //should insert data of passenger here
			coming.setgetontime(geton); coming.setmaxwait(maxwait);
			population.push(coming);

			ArrivalEvent arrive;
			arrivals.push(arrive);

			//cout << Ptype << " "<< time << " " << ID << " " << fromstation << " " << tostation << " " << disability << endl;
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

			//cout << time << " " << ID << endl;
		}
	}

}

Company::~Company()
{
}
