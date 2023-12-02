#include"Company.h"
#include"fifoqueue.h"
#include"priorityqueue.h"
#include"Node.h"
#include"Station.h"
#include <iostream>

using namespace std;

int main()
{
	Company c;
	c.readFile();
	c.simulation();
	c.display();

	/*Station **t=new Station*[1];
	Passenger* psg= new Passenger();

	t[0] = new Station(0);
	ArrivalEvent err(0,0,'A');
	err.setdata("NP","",0,5);
	err.execute(t, 1);

	t[0]->displayinfo();*/

	/*t->insertpassenger(psg);

	t->displayinfo();*/
	
}

