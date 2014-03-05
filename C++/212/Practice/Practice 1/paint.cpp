/*Ident header
//Course: 4002-212
//Author: James Haight
*/

//Includes
#include <iostream>
using namespace std;

//Function Prototypes

int main(){
	//Housekeeping
	cout << fixed << showpoint;
	
	//Variables
	double cans;
	int cansFinal; //non-partial cans!
	int total; //total area of all rooms
	int room1;
	int room2;
	int room3;
	const int door = 21;
	const int window = 20;
	const int feetPerCan = 250;
	
	room1 = ((20+24)*8)-door-window;
	room2 = ((30+40)*8)-door-window;
	room3 = ((16+20)*8)-door-window;
	
	total = room1+room2+room3;
	cans = (double)total/(double)feetPerCan;
	
	cansFinal = cans;
	if(cans > cansFinal){
		cansFinal += 1;
	}
	
	cout << "You will need " << cansFinal << " cans of paint.\n";
	
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
