#include <iostream>
#include <string>
#include <iomanip>

#include "Stack.h"

using std::cout;
using std::endl;
using std::setw;


/*----------------------------------------------
//Name: 1-arg constructor
//Purpose: Construct a stack of specified size
//Parameters: 
//  size - number of elements on stack
//Return: none
*/
Stack::Stack(){
	tosPtr = NULL;
}   

/*----------------------------------------------	
//Name: pop
//Purpose: pop an item off the stack - no check for empty stack
//Parameters: none
*/
int Stack::pop( ){
	int tempInfo;
	StackPtr temp = tosPtr;
	tempInfo = tosPtr->data;
	tosPtr = tosPtr->next;
	return tempInfo;
}
 
/*----------------------------------------------   
//Name: push
//Purpose: put a new item on the stack - no check for full stack
//Parameters:
//  newElem - new item to put on stack
//Return: nothing
*/
void Stack::push(int newElem){
	StackPtr temp;
	temp = new StackNode();
	temp->data = newElem;
	temp->next = tosPtr;
	tosPtr = temp;
}

/*----------------------------------------------	
//Name: isEmpty
//Purpose: test if stack empty
//Parameters: none
//Return: true if empty
*/
bool Stack::isEmpty( ){
	return ( tosPtr == NULL );
}

/*----------------------------------------------	
//Name: isFull
//Purpose: check if stack full
//Parameters: none
//Return: true if full
*/
bool Stack::isFull( ){
	return false;
}

/*----------------------------------------------	
//Name: print
//Purpose: prints contents of stack with marker for top of stack
//Parameters: none
//Return: nothing
*/
void Stack::print( ){
	StackPtr temp = tosPtr;
	if (isEmpty( )){
		cout << "Stack is empty" << endl;
	}
	else{
		while(temp != NULL){
			cout << temp->data << endl;
			temp = temp->next;
		}
		cout << "-----" << endl;
	}
}
	
