/*Ident header
//Course: 4002-210
//Author: James Haight
*/

//Includes
#include <iostream>
#include "MemPen.h"
using namespace std;

//Function Prototypes
void passMemPenByValue(MemPen& p1){p1.print();};

int main(){
	//Housekeeping
	cout << fixed << showpoint;
	
	cout << "\nTesting default constructor of MemPen\n";
	MemPen p1;
	p1.print();
	
	cout << "\nTesting full constructor of MemPen\n";
	MemPen p2(128, 1, 3, "Marks-A-Lot MemPen", 8567, 144, 1.29);
	p2.print();
	
	cout << "\nChange memory to 256\n";
	p2.setMem(256);
	
	cout << "\nCalling passMemPenByValue\n";
	passMemPenByValue(p2);
	
	//terminate program
	return 0;
}

//Function definitions
