#include <iostream>
#include <sstream>
#include "Stack.h"

Stack::Stack() {
    clear();
}

void Stack::push(char c) {
    if (isFull()) {
        std::cout << "ERROR: Stack Overflow!\nPlease pop existing values before pushing new values in\n\n";
    }
    else {
        str[++front] = c;
    }
}

void Stack::pop() {
    if (isEmpty()) {
        std::cout << "ERROR: Empty Stack!\nThere are no values in the stack to pop\n\n";
    }
    else {
        --front;
    }
}

char Stack::peek() {
    char ch = '\0';

    if (!isEmpty()) {
        ch = str[front];
    }
    return ch;
}

bool Stack::isFull() {
    return (front == MAX_CHARS - 1);
}

bool Stack::isEmpty() {
    return (front == -1);
}

void Stack::clear() {
    front = -1;
}

