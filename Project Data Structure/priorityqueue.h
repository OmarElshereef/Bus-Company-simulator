#pragma once
#include "Node.h"
#include <iostream>
using namespace std;

template <class T>
class priorityqueue
{
private:
	Node<T>* head;
	Node<T>* tail;
	int count;

public:
	priorityqueue()
	{
		head = nullptr;
		tail = nullptr;
		count = 0;
	}

	bool isempty()
	{
		return count == 0;
	}

	bool push(T& item, int pri)
	{
		if (isempty())
		{
			head = new Node<T>(item, pri);
			tail = head;
			count++;
			return true;
		}

		else if (tail->getPriority() >= pri)
		{
			Node<T>* temp = new Node<T>(item, pri);
			tail->setNext(temp);
			tail = temp;
			count++;
			return true;
		}

		else if (head->getPriority() < pri)
		{
			Node<T>* temp = new Node<T>(item, pri);
			temp->setNext(head);
			head = temp;
			count++;
			return true;
		}

		else
		{
			Node<T>* temp = head;
			while (temp->getNext())
			{
				if (temp->getNext()->getPriority() < pri)
				{
					Node<T>* ptr = new Node<T>(item, pri);
					ptr->setNext(temp->getNext());
					temp->setNext(ptr);
					count++;
					return true;
				}
				temp = temp->getNext();
			}
		}
	}

	void print()
	{
		Node<T>* temp = head;
		while (temp)
		{
			cout << temp->getItem() << "," << temp->getPriority() << " ";
			temp = temp->getNext();
		}
		cout << endl;
	}

	int size()
	{
		return count;
	}

	bool pop(T& item)
	{
		if (isempty())
			return false;

		else if (count == 1)
		{
			item = head->getItem();
			delete head;
			head = nullptr;
			tail = nullptr;
			count--;
			return true;
		}

		else
		{
			item = head->getItem();
			Node<T>* temp = head->getNext();
			delete head;
			head = temp;
			count--;
			return true;
		}
	}

	T peek()
	{
		return head->getItem();
	}

	T rear()
	{
		return tail->getItem();
	}

	bool remove(T& item)
	{
		if (isempty())
			return false;

		if (head->getItem() == item)
		{
			T dum;
			pop(T);
			count--;
			return true;
		}

		Node<T>* temp = head;
		while (temp->getNext())
		{
			if (temp->getNext()->getItem() == item)
			{
				Node<T>* ptr = temp->getNext();
				temp->setNext(ptr->getNext());
				delete ptr;
				count--;
				return true;
			}
		}

		return false;
	}

	bool searchforpromoted()
	{}

	~priorityqueue()
	{
		Node<T>* dum = head;
		if (!head)
			return;
		Node<T>* ptr = dum->getNext();
		while (ptr)
		{
			delete dum;
			dum = ptr;
			ptr = ptr->getNext();
		}
	}
};



template <class T>
class priorityqueue<T*>
{
private:
	Node<T*>* head;
	Node<T*>* tail;
	int count;

public:
	priorityqueue()
	{
		head = nullptr;
		tail = nullptr;
		count = 0;
	}

	bool isempty()
	{
		return count == 0;
	}

	bool push(T*& item, int pri)
	{
		if (isempty())
		{
			head = new Node<T*>(item, pri);
			tail = head;
			count++;
			return true;
		}

		if (tail->getPriority() >= pri)
		{
			Node<T*>* temp = new Node<T*>(item, pri);
			tail->setNext(temp);
			tail = temp;
			count++;
			return true;
		}

		if (head->getPriority() < pri)
		{
			Node<T*>* temp = new Node<T*>(item, pri);
			temp->setNext(head);
			head = temp;
			count++;
			return true;
		}

		Node<T*>* temp = head;
		while (temp->getNext())
		{
			if (temp->getNext()->getPriority() < pri)
			{
				Node<T*>* ptr = new Node<T*>(item, pri);
				ptr->setNext(temp->getNext());
				temp->setNext(ptr);
				count++;
				return true;
			}
			temp = temp->getNext();
		}
	}

	int size()
	{
		return count;
	}

	bool pop(T*& item)
	{
		if (isempty())
			return false;

		else if (count == 1)
		{
			item = head->getItem();
			delete head;
			head = nullptr;
			tail = nullptr;
			count--;
			return true;
		}

		else
		{
			item = head->getItem();
			Node<T*>* temp = head->getNext();
			delete head;
			head = temp;
			count--;
			return true;
		}
	}

	T* peek()
	{
		return head->getItem();
	}

	T* rear()
	{
		return tail->getItem();
	}

	bool remove(T* item)
	{
		if (isempty())
			return false;

		if (*(head->getItem()) == *item)
		{
			T* dum;
			pop(dum);
			count--;
			return true;
		}

		Node<T*>* temp = head;
		while (temp->getNext())
		{
			if (*(temp->getNext()->getItem()) == *item)
			{
				Node<T*>* ptr = temp->getNext();
				temp->setNext(ptr->getNext());
				delete ptr; // modify if passenger not deleted on leave
				count--;
				return true;
			}
		}

		return false;
	}

	~priorityqueue()
	{
		Node<T*>* dum = head;
		if (!head)
			return;
		Node<T*>* ptr = dum->getNext();
		while (ptr)
		{
			delete dum;
			dum = ptr;
			ptr = ptr->getNext();
		}
	}
};

template<>
class priorityqueue<Passenger>
{
private:
	Node<Passenger>* head;
	Node<Passenger>* tail;
	int count;

public:
	priorityqueue()
	{
		head = nullptr;
		tail = nullptr;
		count = 0;
	}

	bool isempty()
	{
		return count == 0;
	}

	bool push(Passenger& item, int pri)
	{
		if (isempty())
		{
			head = new Node<Passenger>(item, pri);
			tail = head;
			count++;
			return true;
		}

		else if (tail->getPriority() >= pri)
		{
			Node<Passenger>* temp = new Node<Passenger>(item, pri);
			tail->setNext(temp);
			tail = temp;
			count++;
			return true;
		}

		else if (head->getPriority() < pri)
		{
			Node<Passenger>* temp = new Node<Passenger>(item, pri);
			temp->setNext(head);
			head = temp;
			count++;
			return true;
		}

		else
		{
			Node<Passenger>* temp = head;
			while (temp->getNext())
			{
				if (temp->getNext()->getPriority() < pri)
				{
					Node<Passenger>* ptr = new Node<Passenger>(item, pri);
					ptr->setNext(temp->getNext());
					temp->setNext(ptr);
					count++;
					return true;
				}
				temp = temp->getNext();
			}
		}
	}

	void print()
	{
		Node<Passenger>* temp = head;
		while (temp)
		{
			temp->getItem().displayData();
			temp = temp->getNext();
		}
		cout << endl;
	}

	int size()
	{
		return count;
	}

	bool pop(Passenger& item)
	{
		if (isempty())
			return false;

		else if (count == 1)
		{
			item = head->getItem();
			delete head;
			head = nullptr;
			tail = nullptr;
			count--;
			return true;
		}

		else
		{
			item = head->getItem();
			Node<Passenger>* temp = head->getNext();
			delete head;
			head = temp;
			count--;
			return true;
		}
	}

	Passenger peek()
	{
		return head->getItem();
	}

	Passenger rear()
	{
		return tail->getItem();
	}

	bool remove(Passenger& item)
	{
		if (isempty())
			return false;

		if (head->getItem() == item)
		{
			pop(item);
			count--;
			return true;
		}

		Node<Passenger>* temp = head;
		while (temp->getNext())
		{
			if (temp->getNext()->getItem() == item)
			{
				Node<Passenger>* ptr = temp->getNext();
				temp->setNext(ptr->getNext());
				delete ptr;
				count--;
				return true;
			}
		}

		return false;
	}

	bool promote(int curr_time)
	{
		if (isempty())
			return false;

		Node <Passenger>* temp = head;
		if (curr_time - temp->getItem().getarrivetime() == temp->getItem().getmaxwait())
			return true;

		Node <Passenger>* ptr = temp->getNext();
		fifoqueue<Passenger> tempq;

		while (ptr != nullptr)
		{
			if (curr_time - ptr->getItem().getarrivetime() == ptr->getItem().getmaxwait())
			{
				temp->setNext(ptr->getNext());
				Passenger currP = ptr->getItem();
				currP.SetPassengerPriority("aged");
				tempq.push(currP);
				delete ptr;
				ptr = temp->getNext();
			}
			if (ptr == nullptr)
				break;

			temp = temp->getNext();
			ptr = ptr->getNext();
		}

		while (!tempq.isempty())
		{
			Passenger move;
			tempq.pop(move);
			this->push(move, move.GetPassengerPriority());
		}
		return true;
	}

	~priorityqueue()
	{
		Node<Passenger>* dum = head;
		if (!head)
			return;
		Node<Passenger>* ptr = dum->getNext();
		while (ptr)
		{
			delete dum;
			dum = ptr;
			ptr = ptr->getNext();
		}
	}
};
