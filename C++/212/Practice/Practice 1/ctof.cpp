/*Ident header
//Course: 4050-212
//Author: Jim Haight
*/

//Includes
#include <iostream>
using namespace std;

//Function Prototypes

int main(){
	//Housekeeping
	//cout << fixed << showpoint;
	
	//Variables
	float degC;
	float degF;
	
	cout << "Input ye yon celcius temperature: ";
	cin >> degC;
	degF = 32 + (degC*1.8);
	cout << degC << "C is " << degF  << "F"<< endl;

	//terminate program
	system("pause");
	return 0;
}

//Function definitions

/*Name:
//Purpose:
//Parameters:
//Returns:
*/
