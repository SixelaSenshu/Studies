#ifndef __STACK_H__
#define __STACK_H__
#include <ostream>
#include <sstream>  
#include <string>
#include <iostream>


// Exception levée quand on fait top() sur une pile vide.
class EmptyExc {};

class Stack {
    int *s;
	int capacity;
	int count;
 public:
    Stack();               // default constructor, empty stack
    Stack(const Stack &s); // copy constructor
    ~Stack();              // destructor
	int* getStack() const;       // get_stack
    bool isEmpty() const;  // returns true if empty
    int top() const;       // returns the element at the top
    void pop();            // removes element from the top
    void push(int elem);    // puts an element on top
    void clear();          // removes all elements
    int size() const;      // number of elements currently in the stack
    int maxsize() const;   // size of the internal representation
	Stack &operator=(const Stack &other);
	void reduce();
	bool operator==(const Stack &other) const;	
	Stack &operator+=(int elem);
};


std::ostream& operator<<(std::ostream &os, const Stack &stack); 
#endif
