/*Ident header
//Course: 4002-210
//Author: James Haight
*/

//Includes
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "Vehicle.h"
using namespace std;

//Function Prototypes
void readFile(ifstream&, Vehicle[], int);
void printVehicle(Vehicle);

int main(){
	//Housekeeping
	cout << fixed << showpoint;
	
	//Variables
	string filename;
	ifstream fin;
	string line;
	int numCars;
	
	//Get filename from user
	cout << "Input filename: ";
	getline(cin,filename);
	fin.open(filename.c_str());
	if(!fin.is_open()){
		cout << "File not found, exiting.";
		return 1;
	}
	getline(fin,line);
	numCars = atoi(line.c_str());
	Vehicle array[numCars];
	readFile(fin, array, numCars);
	for(int i = 0; i < numCars; i++){
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
		printVehicle(array[i]);
	}

	//terminate program
	return 0;
}

//Function definitions

/*Name: readFile
//Purpose: populates vehicle DB with vehicles from the file
//Parameters: ifstream by reference, vehicle array
//Returns: none
*/
void readFile(ifstream& fin, Vehicle array[], int numCars){
	int currCar = 0;
	bool weGood; //Whether or not the current vehicle is "unique"
	Vehicle defaulto; //Cuz default is a reserved word...
    while(currCar < numCars){
		weGood = true;
		Vehicle temp(fin);
		for(int i = 0; i < currCar; i++){
			if(temp == array[i]){
				weGood = false;
			}
		}
		if(weGood){
			array[currCar] = temp;
		}
		else{
			cout << "\n\tDuplicate detected\n";
			array[currCar] = defaulto;
		}
		currCar++;
	}
}

/*Name: printVehicle
//Purpose: prints a vehicle
//Parameters: vehicle to print
//Returns: none
*/
void printVehicle(Vehicle veh){
	cout << "Vin: " << veh.getVin() << endl
		 << "Manufacturer: " << veh.getManufacturer() << endl
		 << "Color: " << veh.getColor() << endl
		 << "Accessory list:" << endl;
	veh.startAcc();
	while(veh.hasAcc()){
		cout << "\t" << veh.nextAcc() << endl;
	}
}
