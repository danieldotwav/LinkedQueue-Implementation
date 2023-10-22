#include <iostream>
#include "LinkedQueue.h"
#include "Node.h"

//Default Constructor
LinkedQueue::LinkedQueue() : head(nullptr), tail(nullptr) {}

// Destructor
LinkedQueue::~LinkedQueue() {
	clearQueue();
}

// Copy Constructor 
LinkedQueue::LinkedQueue(const LinkedQueue& source) : head(nullptr), tail(nullptr) {
	Node* sourceNode = source.head;

	while (sourceNode != nullptr) {
		Node* newNode = new Node;
		newNode->data = sourceNode->data;
		newNode->next = nullptr;

		if (head == nullptr) { 
			head = tail = newNode; // For First Node: set both head and tail to newNode
		}
		else {
			tail->next = newNode;
			tail = newNode;
		}

		sourceNode = sourceNode->next;
	}
}

// Copy Assignment Operator
// Check first to see if left and right hand operand are NOT equal, then return *this
LinkedQueue& LinkedQueue::operator=(const LinkedQueue& source) {
	if (this != &source) { 
		Node* current = head;
		while (current != nullptr) {
			Node* toDelete = current;
			current = current->next;
			delete toDelete;
		}

		head = tail = nullptr;
		Node* sourceNode = source.head;

		while (sourceNode != nullptr) {
			Node* newNode = new Node;
			newNode->data = sourceNode->data;
			newNode->next = nullptr;

			if (!head) {
				head = tail = newNode;
			}
			else {
				tail->next = newNode;
				tail = newNode;
			}

			sourceNode = sourceNode->next;
		}
	}

	return *this;
}

void LinkedQueue::addNode(char data) {
	Node* newTail = new Node(data);

	if (isEmpty()) {
		head = newTail;
		tail = newTail;
	}
	else {
		tail->next = newTail;
		tail = newTail;
	}
}

void LinkedQueue::removeNode() {
	if (head != nullptr) {
		Node* toDelete = head;
		head = head->next;
		delete toDelete;
	}
}

char LinkedQueue::front() const {
	char headChar = '\0';
	if (head != nullptr) {
		headChar = head->data;
	}
	return headChar;
}

char LinkedQueue::back() const {
	char tailChar = '\0';
	if (tail != nullptr) {
		tailChar = tail->data;
	}
	return tailChar;
}

bool LinkedQueue::isEmpty() const {
	return (head == nullptr);
}

void LinkedQueue::clearQueue() {
	Node* current = head;

	while (current != nullptr) {
		Node* toDelete = current;
		current = current->next;
		delete toDelete;
	}
	head = nullptr;
	tail = nullptr;
}

