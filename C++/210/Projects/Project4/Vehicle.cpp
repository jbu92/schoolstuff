/*Ident header
//Course: 4002-210
//Author: Jim Haight
*/

#include <string>
#include <fstream>
#include <cstdlib>
#include "Vehicle.h"
using namespace std;

/*Name:Vehicle
//Purpose:Default constructor
//Parameters:none
//Returns:none
*/
Vehicle::Vehicle(){
	vin = 999;
	manufacturer = "";
	color = "";
	numAccessories = 0;
}

/*Name:Vehicle
//Purpose:Paramaterized constructor
//Parameters:ifstream by reference
//Returns:none
*/
Vehicle::Vehicle(ifstream& fin){
	string line; //temp variable for current line
	getline(fin,line);
	vin = atoi(line.c_str());
	getline(fin,line);
	manufacturer = line;
	getline(fin,line);
	color = line;
	getline(fin,line);
	price = atof(line.c_str());
	getline(fin,line);
	numAccessories = atoi(line.c_str());
	for(int i = 0; i < numAccessories; i++){
		getline(fin,line);
		accessories[i] = line;
	}
}

/*Name:Vehicle
//Purpose:Copy constructor
//Parameters:Vehicle
//Returns:none
*/
Vehicle::Vehicle(const Vehicle& v2){
	vin = v2.vin; 
	manufacturer = v2.manufacturer;
	color = v2.color;
	price = v2.price;
	numAccessories = v2.numAccessories;
	for(int i = 0; i < numAccessories; i++){
		accessories[i] = v2.accessories[i];
	}
}

/*Name:~Vehicle
//Purpose:Destructor
//Parameters:none
//Returns:none
*/
Vehicle::~Vehicle(){

}

/*Name:operator=
//Purpose:Overload = operator
//Parameters:Vehicle by reference
//Returns:none
*/
void Vehicle::operator=(const Vehicle& v2){
	vin = v2.vin; 
	manufacturer = v2.manufacturer;
	color = v2.color;
	price = v2.price;
	numAccessories = v2.numAccessories;
	for(int i = 0; i < numAccessories; i++){
		accessories[i] = v2.accessories[i];
	}
}

/*Name:operator==
//Purpose:Overload == operator
//Parameters:Vehicle by reference
//Returns:bool 
*/
bool Vehicle::operator==(const Vehicle& v2){
	if(vin == v2.vin &&
	manufacturer == v2.manufacturer &&
	color == v2.color &&
	price == v2.price &&
	numAccessories == v2.numAccessories) {
		return true;
	}
	else{
		return false;
	}
}

/*Name:getVin
//Purpose:Vin accessor
//Parameters:none
//Returns:int Vin
*/
int Vehicle::getVin(){
	return vin;
}

/*Name:getManufacturer
//Purpose:manufacturer accessor
//Parameters:none
//Returns:string Manufacturer
*/
string Vehicle::getManufacturer(){
	return manufacturer;
}

/*Name:getColor
//Purpose:Color accessor
//Parameters:none
//Returns:string Color
*/
string Vehicle::getColor(){
	return color;
}

/*Name:getPrice
//Purpose:Price accessor
//Parameters:none
//Returns:double price
*/
double Vehicle::getPrice(){
	return price;
}

/*Name:startAcc
//Purpose:Initializes accessory accessor
//Parameters:none
//Returns:void
*/
void Vehicle::startAcc(){
	accCounter = 0;
}

/*Name:hasAcc
//Purpose:Accessory accessor
//Parameters:none
//Returns:string of next accessory
*/
string Vehicle::nextAcc(){
	accCounter++;
	return accessories[accCounter-1];
	
}

/*Name:hasAcc
//Purpose:Part of accessory accessor sequence
//Parameters:none
//Returns:bool- T if more accessories, else F
*/
bool Vehicle::hasAcc(){
	if(accCounter < numAccessories){
		return true;
	}
	else{
		return false;
	}
}

/*Name:getModel
//Purpose:Returns model # (or name) of vehicle
//Parameters:none
//Returns:String - model
*/
string Vehicle::getModel(){
	return model;
}

/*Name:getAccPrice
//Purpose:Accesses prices of the specified accessory
//Parameters:int- which accessory to get the price of
//Returns:double - price of given accessory
*/
double getAccPrice(int which){
	return priceList[which];
}
