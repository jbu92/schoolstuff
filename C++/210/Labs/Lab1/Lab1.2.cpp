/*Ident header
//Course: 4002-210
//Author: James Haight
*/

//Includes
#include <iostream>
#include <string>
#include <cstring>
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
	int commas = 0;
	char * inputC, *p;
	
	cout << "Input here yon input: ";
	getline(cin, input);
	inputC = new char [input.size()+1];
	strcpy(inputC, input.c_str());
	
	for(int i = 0; i<input.length(); i++){
		if(inputC[i]==',') commas++;		
	}
	
	if(commas == 4){
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
	}
	else cout << "Invalid input";
	
	
	
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
