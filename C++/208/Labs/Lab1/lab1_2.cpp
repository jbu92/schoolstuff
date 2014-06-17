//Course: 4002-208
//Author: Jim Haight
//Assignment: 4002-208 Lab1_2
//Purpose:.
//Caveats:

//include library for input and output
#include <iostream>
using std::cout;
using std::endl;
using std::cin;

int main ( )
{  
    double manMeters, womanMeters, manMPH, womanMPH;
	
	manMeters = 2.323420074349442;
	womanMeters = 2.071251035625518;
	manMPH = manMeters * (1/0.44704);
	womanMPH = womanMeters*(1/0.44704);
	
	cout << "César Cielo was going " << manMPH << " MPH." << endl;
	cout << "Thereese Alshamma was going " << womanMPH << " MPH." << endl;
    
    //Freeze DOS window until user presses a key.
    cout << endl;
    system("pause");
    //terminate program
    return 0;
} //end of main function
    
