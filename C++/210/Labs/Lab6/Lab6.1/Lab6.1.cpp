/*Ident header
//Course: 4002-210
//Author: James Haight
*/

//Includes
#include <iostream>
#include "Supply.h"
using namespace std;

//Function Prototypes
void updateByVal(Supply, double);
void updateByRef(Supply&, double);

int main(){
	//Housekeeping
	cout << fixed << showpoint;
	
	cout << "Testing default constructor\n";
	Supply s1;
	s1.print();
	
	cout << "Testing full constructor\n";
	Supply stapler("Stapler", 7445, 48, 7.95);
	stapler.print();
	
	cout << "Testing updateByVal\n";
	updateByVal(stapler, 8.50);
	cout << "Price not changed\n";
	stapler.print();
	
	cout << "Testing updateByRef\n";
	updateByRef(stapler, 8.75);
	cout << "Price changed\n";
	stapler.print();
	
	//terminate program
	return 0;
}

//Function definitions

void updateByVal(Supply s1, double price){
	s1.setPrice(price);
	s1.print();
}

void updateByRef(Supply& s1, double price){
	s1.setPrice(price);
	s1.print();
}