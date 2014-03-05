/*Ident header
//Course: 4002-210
//Author: James Haight
*/

//Includes
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

struct Commission{
	int idNum;
	double base,sales,rate;
};

//Function Prototypes
void structPrint(Commission);
void structSetup(Commission&);


int main(){
	//Housekeeping
	cout << fixed << showpoint;
	
	//Variables
	Commission comm;
	structSetup(comm);
	structPrint(comm);

	//terminate program
	return 0;
}

//Function definitions

/*Name: structSetup
//Purpose: Sets up the struct
//Parameters: Commission struct (by reference)
//Returns: nada
*/
void structSetup(Commission& comm){
	cout << "Input ID number: ";
	cin >> comm.idNum;
	cout << "\nInput Base salary: ";
	cin >> comm.base;
	cout << "\nInput sales: ";
	cin >> comm.sales;
	cout << "\nInput commission rate (as decimal percentage (10% = .1)): ";
	cin >> comm.rate;
}

/*Name: structPrint
//Purpose: Prints the struct
//Parameters: Commission struct
//Returns: nada
*/
void structPrint(Commission comm){
	string filename;
	ofstream fout;
	
	cout << setw(8) << "idNum:" << comm.idNum << endl
	 << setw(8) << "base:" 	<< comm.base  << endl
	 << setw(8) << "sales:"	<< comm.sales << endl
	 << setw(8) << "rate:"  << comm.rate;
	
	cout << "\nInput file name: ";
	cin >> filename;
	
	fout.open(filename.c_str(), ios::app);
	
	fout << setw(8) <<	left	<< "idNum:" << comm.idNum << endl
		 << setw(8) <<	left 	<< "base:" 	<< comm.base  << endl
		 << setw(8) <<	left	<< "sales:"	<< comm.sales << endl
		 << setw(8) << 	left	<< "rate:"  << comm.rate << endl;
	fout.close();
}
