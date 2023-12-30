#pragma once
#include<iostream> 
#include<string>



using namespace std;
class UI
{
	static int sim;
public : 

	UI()
	{
	}

	void welcome()
	{
		Print("welcome!\nselect a simulation mode:\n1)interactive mode\n2)silent mode\n");
		cin >> sim;
		getchar();
	}
	template <typename t > 
	void Print(t object)
	{
		cout << object;
	}

	int getsim()
	{
		return sim;
	}

};

