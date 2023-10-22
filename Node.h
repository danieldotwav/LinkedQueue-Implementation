#ifndef NODE_H
#define NODE_H

class Node {
public:
	char data;
	Node* next;
	Node() : data('\0'), next(nullptr) {}
	Node(char d) : data(d), next(nullptr) {}
};

#endif