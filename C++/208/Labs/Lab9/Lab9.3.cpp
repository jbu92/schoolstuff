/*Ident header
//Course: 4002-208
//Author: James Haight
//Assignment:
//Purpose:
//Caveats:
*/

//Includes
#include <iostream>
#include <string>
#include <iomanip>
#include "myInput.h"

using namespace std;



//Function Prototypes
void printDB(string desc[], double weight[], double cost[], int qoh[], int size);
void order(string desc[], int qoh[], int qtyOrdered[], int size);
double costOrder( double cost[], int qtyOrdered[], int size);

int main(){
	//Housekeeping
	cout << fixed << showpoint;
	
	//Constants
	const int SIZE = 4; //Size of the arrays
	
	//Variables
	double cost[SIZE] = {4.99, 4.19, 3.99, 12.99};
	string desc[SIZE] = {"Hikari Sinking Wafers", "Tetramin Tropical Flakes", "Hikari Algae Wafers", "Wardley Shrimp Pellets"};
	double weight[SIZE] = {3.88, 2.2, 2.89, 32};
	int qoh[SIZE] = {6, 4, 0, 5};
	int qtyOrdered[SIZE] = {0, 0, 0, 0};
	double totalCost;
	
	//Dump the DB
	printDB(desc, weight, cost, qoh, SIZE);
	
	//Get orders
	order(desc, qoh, qtyOrdered, SIZE);
	
	//Print orders
	for(int i = 0; i < SIZE; i++){
		cout << qtyOrdered[i] << endl;
	}
	
	//Calc total cost
	totalCost = costOrder(cost, qtyOrdered, SIZE);
	cout << "Cost of the order is: " << setprecision(2) << totalCost;

	//Freeze DOS window until user presses a key.
	cout << endl;
	system("pause");
	//terminate program
	return 0;
}

//Function definitions
/*Name: printDB
//Purpose: Dumps the DB
//Parameters: desc, weight, cost, qoh, size
//Returns: nada
*/
void printDB(string desc[], double weight[], double cost[], int qoh[], int size){
	cout << setw(27) << left << "Name" << setw(6)  << right << "Weight" << setw(8) << "Cost" << setw(8) << "QtyOH" << endl;
	cout << "-------------------------------------------------" << endl;
	for(int i = 0; i < size; i++){
		cout  << setprecision(2) << setw(27) << left << desc[i] << setw(6) << right << weight[i] << setw(8) << cost[i] << setw(8) << qoh[i] << endl;
	}
}

/*Name: order
//Purpose: places an order
//Parameters: Descriptions, number on hand, number ordered, size
//Returns: nada
*/
void order(string desc[], int qoh[], int qtyOrdered[], int size){
	for(int i = 0; i < size; i++){
		string prompt;
		if(qoh[i] > 0){
			prompt = "Quantity to buy of " + desc[i] + ": ";
			qtyOrdered[i] = readIntBetween(prompt, 0, qoh[i]);
		}
	}
}

/*Name: costOrder
//Purpose: calculate order cost
//Parameters: cost, number ordered, size
//Returns: total cost
*/
double costOrder( double cost[], int qtyOrdered[], int size){
	double totalCost = 0; //total cost
	for(int i = 0; i < size; i++){
		totalCost += cost[i] * qtyOrdered[i];
	}
	return totalCost;
}