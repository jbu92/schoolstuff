//***********************************************************************//
//***********************************************************************//
//***                                                                 ***//
//*** PROGRAM:          Average Speed                                 ***//
//*** NAME:             avgSpeed.cpp                                  ***//
//*** LAB:              5                                             ***//
//*** WRITTEN BY:       Jim Haight                                    ***//
//***                                                                 ***//
//*** DESCRIPTION:      This program calculates the average speed of  ***//
//***                   a motor vehicle traveling from the city of    ***//
//***                   origin to the destination city.  The program  ***//
//***                   prompts the user for the origin and the       ***//
//***                   destination.  Then the program prompts the    ***//
//***                   user for the mileage between the two cities.  ***//
//***                   After the user enters the mileage, the program***//
//***                   prompts the user for the total time spent     ***//
//***                   in travel.  When the user enters the time     ***//
//***                   spend in travel, the program outputs the      ***//
//***                   average speed at which the vehicle traveled.  ***//
//***                                                                 ***//
//***********************************************************************//
//***********************************************************************//

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main(void)
{
	
	//constant section
	const int  MINUTES_IN_HOUR = 60;   //minutes per hour
	
	//variable declaration section
	string origin	  = "";  // City of origin
	string destination = "";  // City of destination
	double distance	= 0.0; // Distance between the two cities
	int	hours	   = 0;   // Hours spent traveling
	int	minutes	 = 0;   // Minutes spent traveling
	double travelTime  = 0.0; // Travel time
	double speed	   = 0.0; // Average speed of the vehicle
	char yesno = 'Y';
	
	//***
	//*** Set output format options
	//***
	cout << fixed << showpoint << setprecision(2);
	do{
		//***
		//*** Prompt the user for the city of origin
		//***
		cout << "Enter the city of origin: ";
		getline(cin, origin);
		
		//***
		//*** Prompt the user for the destination
		//***
		cout << "Enter the destination city: ";
		getline(cin, destination);
		
		//***
		//*** Prompt the user for the time spent traveling between the two cities.
		//***   - Prompt the user for hours
		//***   = Prompt the user for minutes
		//***
		cout << endl;
		cout << "Enter the number of hours spent in travel: ";
		cin  >> hours;
		while(hours<0)
		{
			cout << "Please enter a number larger than 0: ";
			cin >> hours;
		}
		cout << "Enter the number of minutes spent in travel:  ";
		cin  >> minutes;
		while(minutes < 0 || minutes > 59)
		{
			cout << "Please enter a number of minutes between 0 and 59: ";
			cin >> minutes;
		}
		
		//***
		//*** CONVERT THE TIME SPENT TRAVELING TO HOURS
		//***
		travelTime = static_cast <double> (hours) +
					static_cast <double> (minutes) / static_cast <double> (MINUTES_IN_HOUR);
					
		//***
		//*** Prompt the user for the distance between the two cities
		//***
		cout << endl;
		do{
			cout << "Enter the distance (in miles) between the two cities: ";
			cin  >> distance;
			if(distance <= 0)
				cout << "Please enter a distance more than 0." << endl;
		} while(distance <= 0);
		
		//***
		//*** CALCULATE THE AVERAGE SPEED OF THE VEHICLE WHILE IN TRAVEL
		//***
		speed = distance / travelTime;
		
		//***
		//*** Output the results
		//***
		cout << endl;
		cout << "The average speed of the vehicle traveling" << endl
			<< "between " << origin << " and " << destination
			<< " is " << speed << " miles per hour." << endl;
		cout << "Would you like to continue? (Y/N) ";
		cin >> yesno;
		yesno = toupper(yesno);
		cin.ignore(1000, '\n');
	}while(yesno == 'Y');
		
	//freeze screen
	cout << endl;
	system("Pause");
	return 0;
}
