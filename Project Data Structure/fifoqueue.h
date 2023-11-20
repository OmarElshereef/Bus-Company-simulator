#include "Node.h"
#include <iostream>
#pragma once
using namespace std;

template <class T>
class fifoqueue
{
private:
	Node<T>* head;
	Node<T>* tail;
	int count;

public:
	fifoqueue()
	{
		head = nullptr, tail = nullptr;
		count = 0;
	}

	bool isempty()
	{
		return count == 0;
	}

	int size()
	{
		return count;
	}

	bool push(T& item)
	{
		Node<T>* temp = new Node<T>(item);

		if (isempty())
		{
			head = temp;
			tail = temp;
			count++;
			return true;
		}

		tail->setNext(temp);
		tail = temp;
		count++;
		return true;
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

		item = head->getItem();
		Node<T>* temp = head;
		head = temp->getNext();
		delete temp;
		count--;
		return true;
	}

	void print()
	{
		Node<T>* temp = head;
		while (temp)
		{
			cout << temp->getItem() << " ";
			temp = temp->getNext();
		}
		cout << endl;
	}

	T peek()
	{
		return head->getItem();
	}

	T rear()
	{
		return tail->getItem();
	}

	~fifoqueue()
	{
		Node<T>* dum = head;
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
class fifoqueue<T*>
{
private:
	Node<T*>* head;
	Node<T*>* tail;
	int count;

public:
	fifoqueue()
	{
		head = nullptr, tail = nullptr;
		count = 0;
	}

	bool isempty()
	{
		return count == 0;
	}

	int size()
	{
		return count;
	}

	bool push(T*& item)
	{
		Node<T*>* temp = new Node<T*>(item);

		if (isempty())
		{
			head = temp;
			tail = temp;
			count++;
			return true;
		}

		tail->setNext(temp);
		tail = temp;
		count++;
		return true;
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

		item = head->getItem();
		Node<T*>* temp = head;
		head = temp->getNext();
		delete temp;
		count--;
		return true;
	}

	T* peek()
	{
		return head->getItem();
	}

	T* rear()
	{
		return tail->getItem();
	}

	~fifoqueue()
	{
		Node<T*>* dum = head;
		Node<T*>* ptr = dum->getNext();
		while (ptr)
		{
			delete dum;
			dum = ptr;
			ptr = ptr->getNext();
		}
	}
};