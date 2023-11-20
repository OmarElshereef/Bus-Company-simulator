#include "Company.h"

Company::Company()
{
}

void Company::readFile()
{
	ifstream reader;
	reader.open("input_file.txt");
	int stations, distance;
	int wbus, mbus, wbuscap, mbuscap;
	int journies, wbusfix, mbusfix;

	reader >> stations >> distance >> wbus >> mbus >> wbuscap >> mbuscap >> journies >> wbusfix >> mbusfix;
	cout << stations << distance << wbus << mbus << wbuscap << mbuscap << journies << wbusfix << mbusfix;
}
