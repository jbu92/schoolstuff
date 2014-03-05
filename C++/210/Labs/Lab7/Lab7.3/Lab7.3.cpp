/*Ident header
//Course: 4002-210
//Author: James Haight
*/

//Includes
#include <iostream>
#include <string>
#include "MemPen.h"
using namespace std;

//Function Prototypes

int main(){
	//Housekeeping
	cout << fixed << showpoint;
	
	//Variables
	int penColor, inkColor, stockNo, quant, mem, numElements;
	double price;
	string desc;
	
	cout << "Enter number of elements: ";
	cin >> numElements;
	Supply* supplyList[numElements];
	

	for(int i = 0; i < numElements; i++){
		supplyList[i] = NULL;
	}
	
	cout << "Enter here yon data for le pen:\n";
	cout << "Enter here yon Pen Color for le pen: ";
	cin >> penColor;
	cout << "Enter here yon Ink Color for le pen: ";
	cin >> inkColor;
	cout << "Enter here yon Name for le pen: ";
	cin.ignore(1000,'\n');
	getline(cin,desc);
	cout << "Enter here yon Stock Number for le pen: ";
	cin >> stockNo;
	cout << "Enter here yon Quantity for le pen: ";
	cin >> quant;
	cout << "Enter here yon Price for le pen: ";
	cin >> price;
	
	supplyList[3] = new Pen(penColor,inkColor,desc,stockNo,quant,price);
	
	cout << "Enter here yon data for le mempen:\n";
	cout << "Enter here yon Pen Color for le mempen: ";
	cin >> penColor;
	cout << "Enter here yon Ink Color for le mempen: ";
	cin >> inkColor;
	cout << "Enter here yon Name for le mempen: ";
	cin.ignore(1000,'\n');
	getline(cin,desc);
	cout << "Enter here yon Stock Number for le mempen: ";
	cin >> stockNo;
	cout << "Enter here yon Quantity for le mempen: ";
	cin >> quant;
	cout << "Enter here yon Price for le mempen: ";
	cin >> price;
	cout << "Enter here yon Memory for le mempen: ";
	cin >> mem;
	
	supplyList[7] = new MemPen(mem,penColor,inkColor,desc,stockNo,quant,price);
	
	cout << "Supply List\n-=-=-=-=-=-=-=-=\n";
	for(int i = 0; i < numElements; i++){
		if(supplyList[i] != NULL){
			supplyList[i]->print();
			cout << endl;
		}
	}
	
	cout << "\n\nPointers:\n";
	for(int i = 0; i < numElements; i++){
		if(supplyList[i] == NULL){
			cout << 0 << endl;
		}
		else{
			cout << supplyList[i] << endl;
		}
	}
	
	for(int i = 0; i < numElements; i++){
		if(supplyList[i] != NULL){
			delete supplyList[i];
			supplyList[i] = NULL;
		}
	}
	delete[] supplyList;
	
	//terminate program
	return 0;
}

//Function definitions
