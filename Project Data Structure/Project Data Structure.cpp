#include"Company.h"
#include"fifoqueue.h"
#include"priorityqueue.h"
#include"Node.h"
#include"Station.h"
#include <iostream>

using namespace std;

int main()
{
	UI ui;
	ui.welcome();
	Company c;
	c.readFile();
	c.simulation();
	
}

