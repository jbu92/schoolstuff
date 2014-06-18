/*Ident header
//Course: 4002-210
//Author: Jim Haight
*/

//Includes
#include <iostream>
#include <cstdlib>
#include "Commission.h"
using namespace std;

//Function Prototypes
bool equal(Commission& comm1, Commission& comm2);
void print(Commission c1);

int main(int argc, char * argv[]){
	//Housekeeping
	cout << fixed << showpoint;
	
	if(argc != 5){ //Argument count checking
		cerr << "Usage: " << argv[0] << " idNum base sales rate";
		return 1;
	}
	
	//Variables
	int idNum = atoi(argv[1]);
	double base = atof(argv[2]);
	double sales = atof(argv[3]);
	double rate = atof(argv[4]);
	Commission commission1(idNum, base, sales, rate);
	Commission commission2(1, 2, 3, 4);
	
	cout << "Commission c1: ";
	print(commission1);
	commission2 = commission1;
	cout << "Commission c2 (after assignment): ";
	print(commission2);
	if(commission1 == commission2){
		cout << "They are equal using ==\n";
	}
	if(equal(commission1, commission2)){
		cout << "Equal using equal function\n";
	}
	Commission c3;
	c3.copy(commission2);
	cout << "Commission c3: ";
	print(c3);
	
	
	//terminate program
	system("pause");
	return 0;
}

//Function definitions

/*Name: equal
//Purpose:
//Parameters:
//Returns:
*/
bool equal(Commission& comm1, Commission& comm2){
	if(comm1.idNum == comm2.idNum && comm2.sales == comm1.sales && comm1.rate == comm2.rate && comm1.base == comm2.base)
		return true;
	else
		return false;
}

void print(Commission c1){
	cout << "\nidNum: " << c1.getIdNum() << "\nBase: " << c1.getBase() << "\nSales: " << c1.getSales() << "\nRate: " << c1.getRate() << endl;
}
