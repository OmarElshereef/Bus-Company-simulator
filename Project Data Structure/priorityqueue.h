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

	/*void print()
	{
		Node<T>* temp = head;
		while (temp)
		{
			cout << temp->getItem() << "," << temp->getPriority() << " ";
			temp = temp->getNext();
		}
		cout << endl;
	}*/

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
			else
				temp = (temp->getNext());
		}

		return false;
	}


	int sizebypri(int priority)
	{
		int t = 0;
		Node<T>* temp = head;
		while (temp)
		{
			if (temp->getItem()->GetPassengerPriority() == priority)
			{
				t++;
			}
			temp = temp->getNext();
		}

		return t;
	}

	/*bool PrintByPriority(int pri)
	{
		bool t = false;
		Node<T>* temp = head;
		while (temp != nullptr)
		{
			if (temp->getPriority() == pri)
			{
				temp->getItem()->display();
				temp = temp->getNext();
				t = true;
			}
			else if (temp->getPriority() > pri)
			{
				return t;
			}
			else if(temp->getPriority() < pri)
			temp = temp->getNext();

		}
		return t;
	}*/

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

	bool push(T* item, int pri)
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

	/*void print()
	{
		Node<T*>* temp = head;
		while (temp != nullptr)
		{
			temp->getItem()->display();
			temp = temp->getNext();
		}
	}*/

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
			temp = temp->getNext();
		}

		return false;
	}

	int sizebypri(int priority)
	{
		int t=0 ; 
		Node<T*>* temp = head;
		while (temp)
		{
			if (temp->getItem()->GetPassengerPriority() == priority)
			{
				t++;
			}
			temp = temp->getNext();
		}

		return t;
	}

	/*bool PrintByPriority(int pri)
	{
		bool t = false;
		Node<T*>* temp = head;
		while (temp != nullptr)
		{
			if (temp->getPriority() == pri)
			{
				temp->getItem()->display();
				temp = temp->getNext();
				t = true;
			}
			else if (temp->getPriority() > pri)
			{
				temp = temp->getNext();
			}
			else if(temp->getPriority() < pri)
			{
				return t;
			}
		}
		return t;
	}*/

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
