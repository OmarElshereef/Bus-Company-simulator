#ifndef _NODE
#define _NODE

//First let's declare a single node in the list
template<typename T>
class Node
{
private:
	T item;	// A data item (can be any complex sturcture)
	int priority;
	Node<T>* next;	// Pointer to next node
public:

	Node() //default constructor
	{
		next = nullptr;
	}

	Node(T& newItem) //non-default constructor
	{
		item = newItem;
		next = nullptr;
		priority = -1;

	}

	Node(T& newitem, int pri)
	{
		item = newitem;
		next = nullptr;
		priority = pri;
	}

	void setItem(T& newItem)
	{
		item = newItem;
	} // end setItem

	void setNext(Node<T>* nextNodePtr)
	{
		next = nextNodePtr;
	} // end setNext

	void setPriority(int p)
	{
		priority = p;
	}

	int getPriority()
	{
		return priority;
	}

	T getItem() const
	{
		return item;
	} // end getItem

	Node<T>* getNext() const
	{
		return next;
	}

	~Node()
	{}// end Node
};


template<typename T>
class Node<T*>
{
private:
	T* item;	// A data item (can be any complex sturcture)
	int priority;
	Node<T*>* next;	// Pointer to next node
public:

	Node() //default constructor
	{
		next = nullptr;
	}

	Node(T*& newItem) //non-default constructor
	{
		item = newItem;
		next = nullptr;
		priority = -1;

	}

	Node(T*& newitem, int pri)
	{
		item = newitem;
		next = nullptr;
		priority = pri;
	}

	void setItem(T*& newItem)
	{
		item = newItem;
	} // end setItem

	void setNext(Node<T*>* nextNodePtr)
	{
		next = nextNodePtr;
	} // end setNext

	void setPriority(int p)
	{
		priority = p;
	}

	int getPriority()
	{
		return priority;
	}

	T* getItem() const
	{
		return item;
	} // end getItem

	Node<T*>* getNext() const
	{
		return next;
	}

	~Node()
	{}
}; // end Node
#endif	

