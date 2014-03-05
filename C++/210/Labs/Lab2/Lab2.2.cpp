#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

#include "Lab2.2.h"



//prototypes
void print(Commission& emp);

int main (){
	{
		//set print options
		cout << fixed << showpoint << setprecision(2);
		
		//variable declaration
		int	idNum = 0;   //hold input for id num
		double base  = 0.0; //hold input for base
		double sales = 0.0; //hold input for sales
		double rate  = 0.0; //holds input for rate
		
		//Initialize Commission object fred with base salary of $500
		//  sales of $2000 and commission rate of 10%
		Commission fred(111, 500.00, 2000.00, 0.10); 
		print(fred);
		
		//Create Commission object joe as default
		Commission joe;
		print(joe);
		
		//get all attribute values for joe object
		
		//set id num for joe
		cout << endl;
		while (true)
		{
			cout << "Enter id number: ";
			cin >> idNum;

			if (joe.setIdNum(idNum)) 
			   break;
			cout << "\tInvalid IdNum - must be between "
				 << "0 and 999, inclusively\n";
		}
		print(joe);
		
		//set base for joe
		cout << endl;
		while (true)
		{
			cout << "Enter base amount: ";
			cin >> base;

			if (joe.setBase(base)) 
			   break;
			cout << "\tInvalid base - must be > 0\n";
		}
		print(joe);
			
		//set sales for joe
		cout << endl;
		while (true)
		{
			cout << "Enter sales: ";
			cin >> sales;
			if (joe.setSales(sales)) break;
			cout << "\tInvalid sales - must be >= 0\n";
		}
		print(joe);  
		
		//set rate for joe
		cout << endl;
		while (true)
		{
			cout << "Enter rate: "; 
			cin >> rate; 
			if (joe.setRate(rate)) break;
			cout << "\tInvalid rate - must be > 0.0 and <= 0.20\n";
		}
		print(joe);
		cout << endl;
	} //destruct joe and fred here
	
	return 0;  
} //end main

//-------------------------------
//Name: print
//Purpose: print information for an employee on commission
//Parameters: 
//  emp - employee on commission
//Returns: nothing
//-------------------------------
void print(Commission& emp){
	cout << "--------" << endl;
	cout << "Id Num: " << emp.getIdNum()   << endl; 
	cout << "Base: " << emp.getBase();
	cout << "  Sales: " << emp.getSales();
	cout << "  Rate: " << emp.getRate(); 
	cout << "  Salary: " << emp.calcSalary() << endl;
	cout << "--------" << endl;  
}
