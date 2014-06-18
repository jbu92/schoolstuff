/*Ident header
//Course: 4002-210
//Author: Jim Haight
*/

//Includes
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//Function Prototypes

int main(){
	//Housekeeping
	cout << fixed << showpoint;
	
	//Variables
	string input;
	string name;
	string address;
	string city;
	string state;
	string zip;
	
	cout << "Input here yon input: ";
	getline(cin, input);
	
	name = input.substr(0, input.find(","));
	input = input.substr(input.find(",") + 1, input.length());
	address = input.substr(0, input.find(","));
	input = input.substr(input.find(",") + 1, input.length());
	city = input.substr(0, input.find(","));
	input = input.substr(input.find(",") + 1, input.length());
	state = input.substr(0, input.find(","));
	input = input.substr(input.find(",") + 1, input.length());
	zip = input.substr(0, input.length());
	
	cout << name << endl << address << endl << city << ", " << state << " " << zip << endl;
	
	if(zip.length() != 5 && zip.length() != 10) cout << "Zip is invalid, brah";
	else cout << "Zip is valid";
	
	
	
	//Freeze DOS window until user presses a key.
	cout << endl;
	system("pause");
	//terminate program
	return 0;
}

//Function definitions

/*Name:
//Purpose:
//Parameters:
//Returns:
*/
