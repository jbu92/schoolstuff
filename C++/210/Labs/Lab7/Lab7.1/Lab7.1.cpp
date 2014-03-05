/*Ident header
//Course: 4002-210
//Author: James Haight
*/

//Includes
#include <iostream>
#include "MemPen.h"
using namespace std;

//Function Prototypes

int main(){
	//Housekeeping
	cout << fixed << showpoint;
	
	Supply* supplyList[10];
	for(int i = 0; i < 10; i++){
		supplyList[i] = NULL;
	}
	
	Pen p1(2,1,"Uni-BAll Elite", 8567,144,6.99);
	supplyList[0] = &p1;
	
	MemPen mp1(128, 1, 3, "Marks-A-Lot MemPen", 8567, 144, 1.29);
	supplyList[2] = &mp1;
	
	cout << "Supply List\n-=-=-=-=-=-=-=-=\n";
	for(int i = 0; i < 10; i++){
		if(supplyList[i] != NULL){
			supplyList[i]->print();
			cout << endl;
		}
	}
	
	
	//terminate program
	return 0;
}

//Function definitions
