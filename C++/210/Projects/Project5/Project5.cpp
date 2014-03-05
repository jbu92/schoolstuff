/*Ident header
//Course: 4002-210
//Author: James Haight
*/

//Includes
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <string.h>
#include "Stack.h"
using namespace std;

//Function Prototypes

int main(){
	//Housekeeping
	cout << fixed << showpoint;
	
	//Variables
	string input = ""; //Input line
	char cInput[100]; //C-string buffer for input
	stringstream outString; //stringstream, from sstream, useful for "couting" to strings
	Stack myStack; //Object from Stack class
	char * token; //Token pointer, used to break up input
	double operand1,operand2,result; //To be used when doing maths.
	
	//Usage info
	cout << "Usage: enter postfix expression, space-separated.\nq or quit to exit.\nUnsupported input results in garbage\n";
	
	while(input.compare("q") != 0 && input.compare("quit") != 0){ //While not requesting to quit
		//Get input
		cout << "Enter Command: ";
		getline(cin,input);
		while(input.compare("") == 0){
			cout << "No, seriously, enter a command... ";
			getline(cin,input);
		}
		
		if(input.compare("q") != 0 && input.compare("quit") != 0){ //If they don't request to quit...
			strcpy(cInput,input.c_str()); //Transfer the input to a c-string buffer
			token = strtok(cInput," "); //And start the process of breaking it up
			
			while(token != NULL){ //Until we reach the end of the input...
				//Decide what the next chunk is.
				if(strcmp(token,"/") == 0){ //If it's a division operator...
					//Pop the top two off the stack
					operand2 = atof(myStack.pop().c_str());
					operand1 = atof(myStack.pop().c_str());
					
					result = operand1/operand2; //Divide them					
					outString << result; //"cout" the result into a string					
					myStack.push(outString.str()); //Push that string to the stack
					outString.str(""); //And reset the "cout" string thingy
				}
				else if(strcmp(token,"*") == 0){ //Similar process for multiplication...
					operand2 = atof(myStack.pop().c_str());
					operand1 = atof(myStack.pop().c_str());
					result = operand1*operand2;
					outString << result;
					myStack.push(outString.str());
					outString.str("");
				}
				else if(strcmp(token,"+") == 0){ //And addition...
					operand2 = atof(myStack.pop().c_str());
					operand1 = atof(myStack.pop().c_str());
					result = operand1+operand2;
					outString << result;
					myStack.push(outString.str());
					outString.str("");
				}
				else if(strcmp(token,"-") == 0){ //And subtraction.
					operand2 = atof(myStack.pop().c_str());
					operand1 = atof(myStack.pop().c_str());
					result = operand1-operand2;
					outString << result;
					myStack.push(outString.str());
					outString.str("");
				}
				else{ //If it ISN'T an operator, it must be an operand, so...
					if(atof(token)){
						myStack.push(token); //Push it to the stack
						cout << "pushing token: " << token << endl; //And notify the user
					}
					else{
						cerr << "encountered unsupported input.\n";
					}
				}
				token = strtok(NULL," "); //Almost forgot to get the next chunk of input, didn't you?
			}
			cout << "Results: " << myStack.pop() << endl; //Once we're at the end of the input, spit out the results
			
			if(!myStack.isEmpty()){ //Make sure the stack is empty
				//If not, output an error and reset the stack
				cerr << "But that's probably not right, because something went wrong. Please check your input.\n";
				while(!myStack.isEmpty()){
					myStack.pop();
				}
			}
		}
	}
	
	//terminate program
	return 0;
}

//Function definitions

/*Name:
//Purpose:
//Parameters:
//Returns:
*/
