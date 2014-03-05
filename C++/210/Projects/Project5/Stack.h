#include <string>
using namespace std;
#ifndef STACK_H
#define STACK_H

struct StackNode{
	string data;
	StackNode* next;
};

typedef StackNode* StackPtr;

class Stack{
	private:
		StackPtr tosPtr;
	public:
		Stack();		//create a stack with specified number of items  
		string pop( );		//pop top item from stack
		void push(string);	 //push new item on stack
		bool isEmpty( );	//returns true if stack empty
		bool isFull( ){};	 //returns true if stack full //Nuked on account of not being necessary here...
		void print( ){};	  //prints contents of stack //Nuked on account of not being necessary here...
	
};

#endif

