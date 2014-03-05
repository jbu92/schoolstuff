#include <iostream>
#include <string>
#include <iomanip>

#include "Stack.h"

using namespace std;


int main (){
	Stack myStack;   //stack of 4 elements
	string op;  //name of operation to be performed
	int num; //number to be pushed	
	
	cout << "Testing of stack class" << endl;
	cout << "Valid operations are push, pop, print, quit" << endl;
	
	while (true)
	{   //prompt user to enter command
		cout << endl << "Enter command: ";
		cin >> op;
		cin.ignore(1000, '\n');
		
		//test for command and carry out operation

		//PUSH operation
		if (op == "push"){   //push if stack is not full
		   if (myStack.isFull()){
				cout << "Can not push value as stack is full" << endl;
			}
			else
			{
				cout << "Enter value: ";
				cin >> num;
				cin.ignore(1000, '\n');
				myStack.push(num);
			}
		}

		//POP operation
		else if (op == "pop"){   //pop if stack is not empty
			if (myStack.isEmpty())
				cout << "Can not pop value as stack is empty" << endl;
			else
				cout << "Item popped off stack is " << myStack.pop() << endl;
		}

		//PRINT operation
		else if (op == "print")
			myStack.print();

		//QUIT program
		else if (op == "quit"){   //print stack and quit
			cout << "Stack at end of program" << endl;
			myStack.print();
			break;
		}

		//ERROR - invalid operation
		else
			cout << "Invalid operation" << endl;
	} //end loop
	
	cout << endl;	   
	return 0;  
} //end main

