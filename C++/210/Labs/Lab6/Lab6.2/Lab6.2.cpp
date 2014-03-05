/*Ident header
//Course: 4002-210
//Author: James Haight
*/

//Includes
#include <iostream>
#include "Pen.h"
using namespace std;

//Function Prototypes


int main(){
	//Housekeeping
	cout << fixed << showpoint;
	
	cout << "\nTesting default constructor of Pen\n";
	Pen p1;
	p1.print();
	
	cout << "\nTesting full constructor of Pen\n";
	Pen p2(1, 3, "Marks-A-Lot", 8567, 144, 1.29);
	p2.print();
	
	cout << "\nChange price to 1.47\n";
	p2.setPrice(1.47);
	p2.print();
	
	cout << "\nChange pen color to blue\n";
	p2.setPenColor(C_BLUE);
	p2.print();
	
	//terminate program
	return 0;
}

//Function definitions
