/*Ident header
//Course: 4002-212
//Author: Jim Haight
*/

//Includes
#include <iostream>
using namespace std;

//Function Prototypes

int main(){
	//Housekeeping
	cout << fixed << showpoint;
	
	//Variables
	double diameter;
	double depth;
	double volume;
	double volumeGal;
	
	cout << "Protip: use feet for all measures\n";
	cout << "Enter ye here yon diameter of yon lake: ";
	cin >> diameter;
	cout << "Enter ye here yon depth of yon lake: ";
	cin >> depth;
	volume = (3.1415926535897 * ((diameter / 2)*(diameter/2)) * depth);
	volumeGal = volume * 7.5;
	cout << "Diameter: " << diameter << "\nDepth: " << depth << "\nVolume: " << volume << "\nGallons: " << volumeGal << endl;

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
