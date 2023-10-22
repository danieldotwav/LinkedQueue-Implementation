#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H
#include "Node.h"

class LinkedQueue {
private:
	Node* head;
	Node* tail;

public:
	LinkedQueue();
	~LinkedQueue();
	LinkedQueue(const LinkedQueue& source); // Copy Constructor
	LinkedQueue& operator=(const LinkedQueue& source); // Copy Assignment Operator

	void addNode(char data);
	void removeNode();
	char front() const;
	char back() const;
	
	bool isEmpty() const;
	void clearQueue();
};

#endif
