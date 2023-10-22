#ifndef STACK_H
#define STACK_H

const int MAX_CHARS = 65; // Max characters that can be processed in a line

class Stack {
private:
	char str[MAX_CHARS];
	int front;

public:
	Stack();
	void push(char c);
	void pop();
	char peek();

	bool isFull();
	bool isEmpty();
	void clear();
};

#endif