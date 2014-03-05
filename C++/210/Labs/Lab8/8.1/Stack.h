#ifndef STACK_H
#define STACK_H

struct StackNode{
	int data;
	StackNode* next;
};

typedef StackNode* StackPtr;

class Stack{
	private:
		StackPtr tosPtr;
	public:
		Stack();		//create a stack with specified number of items  
		int pop( );		//pop top item from stack
		void push(int);	 //push new item on stack
		bool isEmpty( );	//returns true if stack empty
		bool isFull( );	 //returns true if stack full
		void print( );	  //prints contents of stack
	
};

#endif

