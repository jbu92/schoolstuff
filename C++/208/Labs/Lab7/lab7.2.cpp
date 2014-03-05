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
double calcTaxFica(double, double);
double calcTaxFed(double, double, int);
double calcTaxedIncome(double, double);

int main (){
	//Housekeeping
	cout << fixed << showpoint << setprecision(2);
	
	//constant section
	const double FED_MINIMUM_WAGE = 7.25;  //minimum federal wage
	const double TAX_RATE_FICA = .0765; //FICA tax rate
	//Tax brackets for income taxes
	const double TAX1 = .1; //0-8500
	const double TAX2 = .15; //8500-34500
	const double TAX3 = .25; //34500+
	const int TAX_B1 = 8500; //Bracket 1 max
	const int TAX_B2 = 34500; //Bracket 2 max
	const int FILEFEE = 5800; //filing fee
	
	//variable section
	double hours	  = 0.0;	//hours worked during the week. 
	double hourlyRate = 0.0;	//hourly rate of pay
	double weeklyWage = 0.0;	//weekly wage
	double incomeTaxRate; //income tax rate
	double ficaTax; //fica tax
	double incomeTax; //income tax
	double totalTax; //sum of the two above
	double netWages; //wages - tax
	double yearlyWages; //weeklyWage * 52
	int taxBracket;
	double taxableIncome; //taxable income
	
	//print heading
	cout << "Program to calculate weekly pay for hourly employees, with taxes" << endl << endl;
	
	//read hours between 0 and 40
	hours = readDoubleBetween("Enter hours worked: ", 0.0, 40.0);	  
	
	//read hourly rate between federal minimum wage of 7.25 and 25.00
	hourlyRate = readDoubleBetween("Enter hourly wage (between 7.25 and 25): ", 7.25, 25.00);
	
	//calculate weekly wage
	weeklyWage = calcWage(hourlyRate, hours);
	yearlyWages = weeklyWage * 52;
	taxableIncome = yearlyWages - FILEFEE;
	
	//calculate income tax rate
	if(taxableIncome <= TAX_B1){
		taxBracket = 1;
		incomeTaxRate = TAX1;
	}
	else if(taxableIncome <= TAX_B2){
		taxBracket = 2;
		incomeTaxRate = TAX2;
	}
	else{
		taxBracket = 3;
		incomeTaxRate = TAX3;
	}
	
	//Calculate taxes
	ficaTax = calcTaxFica(TAX_RATE_FICA, weeklyWage);
	incomeTax = calcTaxFed(incomeTaxRate, weeklyWage, taxBracket);
	totalTax = ficaTax + incomeTax;
	
	//Calculate Net wage
	netWages = calcTaxedIncome(weeklyWage, totalTax);
/*	
	//Print tax info
	cout << "\n\n";
	cout << "Taxable Income: " << yearlyWages - 5800<< endl;
	cout << "Annual tax at " << incomeTaxRate * 100 << "%: " << calcTaxFed(incomeTaxRate, weeklyWage, taxBracket)*52;
	cout << "\n\n";
*/
	//print gross wage, taxes, and net wage
	cout << left << setw(13) << "Gross Wage" << right << setw(8) << weeklyWage 	<< endl;
	cout << left << setw(13) << "FICA tax"	 << right << setw(8) << ficaTax		<< endl;
	cout << left << setw(13) << "Income Tax" << right << setw(8) << incomeTax	<< endl;
	cout << left << setw(13) << "Net Wage"	 << right << setw(8) << netWages	<< endl;
	
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

/*Name: calcTaxFica
//Purpose: Calculates FICA tax
//Parameters: 
// double tax rate
// double monies to be taxed
//Returns: Tax
*/
double calcTaxFica(double taxrate, double income){
	double tax = taxrate * income;
	return tax;
}

/*Name: calcTaxFed
//Purpose: Calculates Federal income tax
//Parameters: 
// double tax rate
// double monies to be taxed
//Returns: Tax
*/
double calcTaxFed(double taxrate, double income, int bracket){
	const int FILEFEE = 5800; //filing fee
	double tax;
	income = income * 52;
	income -= FILEFEE;
	if(income > 0){
		switch(bracket){
			case 1:
				tax = income * taxrate;
				tax = tax / 52;
				break;
			case 2:
				income -= 8500;
				tax = taxrate * income;
				tax += 850;
				tax = tax / 52;
				break;
			case 3:
				income -= 34500;
				tax = taxrate * income;
				tax += 4750;
				tax = tax / 52;
				break;
		}
	}
	else tax = 0;
	return tax;
}

/*Name: calcTaxedIncome
//Purpose: Calculates taxed income
//Parameters: 
// double income
// double taxes
//Returns: Net income
*/
double calcTaxedIncome(double income, double taxes){
	double money = income - taxes;
	return money;
}
