/*Ident header
//Course: 4002-210
//Author: James Haight
*/
#include <string>
#include <fstream>
using namespace std;

#ifndef VEHICLE_H
#define VEHICLE_H
class Vehicle{
	private:
		int vin; 
		string manufacturer;
		string color;
		double price;
		int numAccessories;
		string *accessories;
		int accCounter; //For cycling through accessory list
		string model;
		double *priceList;
	public:
		Vehicle(); //Default constructor
		Vehicle(ifstream&); //Reads data from file
		Vehicle(const Vehicle&); //Copy constructor
		~Vehicle(); //Destructor
		void operator=(const Vehicle&);
		bool operator==(const Vehicle&);
		int getVin();
		string getManufacturer();
		string getColor();
		double getPrice();
		void startAcc(); //Sets accCounter to 0
		string nextAcc(); //Returns next accessory
		bool hasAcc(); //More accessories?
		string getModel;
		double getAccPrice(int);
		
};

#endif
