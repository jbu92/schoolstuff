/*Ident header
//Course: 4002-212
//Author: Jim Haight
*/

//Includes
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Bars{
	string symbols;
};

int main(){
	//Housekeeping
	cout << fixed << showpoint;
	
	//Variables
	char zipCode[5]; //Input zip code
	Bars output[6]; //Array of outputs
	int checkDigit; //Check digit
	int checkSum = 0; //sum of current digits (used to calculate check digit)
	
	cout << "Iput ye here yon zip code: ";
	cin >> zipCode;

	
	for(int i = 0;i<5;i++){
		switch(zipCode[i]){
			case '1':
				output[i].symbols = ":::||";
				break;
			case '2':
				output[i].symbols = "::|:|";
				break;
			case '3':
				output[i].symbols = "::||:";
				break;
			case '4':
				output[i].symbols = ":|::|";
				break;
			case '5':
				output[i].symbols = ":|:|:";
				break;
			case '6':
				output[i].symbols = ":||::";
				break;
			case '7':
				output[i].symbols = "|:::|";
				break;
			case '8':
				output[i].symbols = "|::|:";
				break;
			case '9':
				output[i].symbols = "|:|::";
				break;
			case '0':
				output[i].symbols = "||:::";
				break;
		}
		checkSum += zipCode[i]-'0';
	}
	checkDigit = 10 - (checkSum - 10*(checkSum / 10));
	
	
	switch(checkDigit){
	case 1:
		output[5].symbols = ":::||";
		break;
	case 2:
		output[5].symbols = "::|:|";
		break;
	case 3:
		output[5].symbols = "::||:";
		break;
	case 4:
		output[5].symbols = ":|::|";
		break;
	case 5:
		output[5].symbols = ":|:|:";
		break;
	case 6:
		output[5].symbols = ":||::";
		break;
	case 7:
		output[5].symbols = "|:::|";
		break;
	case 8:
		output[5].symbols = "|::|:";
		break;
	case 9:
		output[5].symbols = "|:|::";
		break;
	case 0:
		output[5].symbols = "||:::";
		break;
	}
	
	cout << "|";
	for(int i=0; i<6; i++)
		cout << output[i].symbols;
	cout << "|";
	
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
