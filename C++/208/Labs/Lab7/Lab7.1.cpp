/*Course: 4002-208
//Author: Rayno Niemi (James Haight Modified)
//Starting Program of Lab 7
//Name: Lab7Ex1.cpp
//Purpose: Compute the hourly wage of an employee.  No overtime
*/

//Includes
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

//function prototypes 
double readDoubleBetween(string, double, double);
double calcWage(double, double);

int main (){
	//Housekeeping
	cout << fixed << showpoint << setprecision(2);
	
	//constant section
	const double FED_MINIMUM_WAGE = 7.25;  //minimum federal wage
	
	//variable section
	double hours	  = 0.0;	//hours worked during the week. 
	double hourlyRate = 0.0;	//hourly rate of pay
	double weeklyWage = 0.0;	//weekly wage
	

	
	//print heading
	cout << "Program to calculate weekly gross pay for hourly employees" << endl << endl;
	
	//read hours between 0 and 40
	hours = readDoubleBetween("Enter hours worked: ", 0.0, 40.0);	  
	
	//read hourly rate between federal minimum wage of 7.25 and 25.00
	hourlyRate = readDoubleBetween("Enter hourly wage (between 7.25 and 25): ", 7.25, 25.00);
	
	//calculate weekly wage
	weeklyWage = calcWage(hourlyRate, hours);
	
	//print gross wage
	cout << left << setw(13) << "Gross Wage"  << right << setw(8) << weeklyWage << endl;
	  
	//freeze console window
	cout << endl;
	system("Pause");
	return 0;  
} //end main



/*Name: readDoubleBetween
//Purpose: read a double between two given values
//Parameters:
//  prompt - user prompt
//  lowValue - lowest acceptable value
//  highValue - highest acceptable value
//Returns: number between lowValue and highValue, inclusively
*/

double readDoubleBetween(string prompt, double lowValue, double highValue){
	double input;
	do{
		cout << prompt;
		cin >> input;
		if(input < lowValue || input > highValue) cout << "Error, input must fall between " << lowValue << " and " << highValue << endl;
	} while(input < lowValue || input > highValue);
	return input;
}

/*Name: calcWage
//Purpose: Calculates wages based on wage and hours worked
//Parameters: 
// double wage- hourly wage
// double hours- hours worked
//Returns: Wage
*/
double calcWage(double wage, double hours){
	double money = wage * hours; //Wages paid
	return money;
}

