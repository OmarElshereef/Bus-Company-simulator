
class Company
{
private:

	fifoqueue<ArrivalEvent> arrivals;
	fifoqueue<Passenger> population;
	fifoqueue<LeaveEvent> leaves;

public:
	Company();
	
	void readFile();

	~Company();
	
};
