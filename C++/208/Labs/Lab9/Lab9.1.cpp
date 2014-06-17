/*Ident header
//Course: 4002-208
//Author: Jim Haight
//Assignment:
//Purpose:
//Caveats:
*/

//Includes
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

//Function Prototypes
void printDB(string desc[], double weight[], double cost[], int qoh[], int size);

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
	
	//Dump the DB
	printDB(desc, weight, cost, qoh, SIZE);

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
