/*Ident header
//Course: 4002-210
//Author: Jim Haight
*/

//Includes
#include <cstring>
#include <iostream>
using namespace std;

//Function Prototypes
void reverse(char[]);

int main(int argc, char* argv[]){
	//Housekeeping
	cout << fixed << showpoint;
	
	//Variables
	char message[strlen(argv[1])];

	
	//Move ye yon string
	strcpy(message,argv[1]);
	
	//Run le reversal
	reverse(message);
	
	//Print les results
	cout << message;
	
	//terminate program
	system("pause");
	return 0;
}

//Function definitions

/*Name:
//Purpose:
//Parameters:
//Returns:
*/
void reverse(char message[]){
	int length = strlen(message);
	char * front = message;
	char * rear = message+length-1;
	char temp;
	for(int i = 0; i < length/2; i++){
	//	cout << "pre:\nFront=" << *front <<"\nRear=" << *rear << endl;
		temp = *front;
		*front = *rear;
		*rear = temp;
	//	cout << "post:\nFront=" << *front <<"\nRear=" << *rear << endl;
		front = front+1;
		rear = rear-1;
	}
}
