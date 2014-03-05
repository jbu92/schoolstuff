/* Course: 4002-208
// Author: Rayno Niemi
// Purpose: Implementation of general input routines detecting improperly formatted input numbers
*/
#include <iostream>
#include <string>
using namespace std;

/*Name: readDouble
//Purpose: read in a double based on the prompt
//Parameters:
//	  prompt - message to display to user
//Returns: input value
*/
double readDouble(string prompt){
	double number;
	
	//attempt to read first double input
	cout << prompt;  
	cin >> number;
	
	//did user enter a properly formatted double number
	while (cin.fail()){
		cout << "\tImproperly double number\n";
		cin.clear();
		cin.ignore(1000, '\n');
		
		//attempt to read next double input
		cout << "Enter number: ";  
		cin >> number;	 
	}
	
	//flush any extraneous user input in buffer, especially newline
	cin.ignore(1000, '\n');
	return number;
}


/*Name: readDoublePos
//Purpose: read a positive double number  based on the prompt
//Parameters:
//	  prompt - message to display to user
//Returns: positive input value
*/
double readDoublePos(string prompt){
	double number;
	
	//call readDouble to read a properly formatted double number
	number = readDouble(prompt);
	
	//prompt user if input is not positive
	while(number <= 0.0){
		cout << "\tInvalid double input - must be positive" << endl;
		
		//call readDouble to read a properly formatted double number
		number = readDouble(prompt);
	}			 
	return number;
}


/*Name: readDoubleBetween
//Purpose: read a double number between two specified values the prompt
//Parameters:
//	  prompt - message to display to user
//	  min - minimum acceptable value
//	  max - maximum acceptable value
//Returns: input value between minimum and maximum acceptable values
*/
double readDoubleBetween(string prompt, double min, double max){
	double number;

	//call readDouble to read a properly formatted double number	
	number = readDouble(prompt);
	
	//get more user input if number is not in range.
	while(number < min || number > max){
		cout << "\tInvalid double input - must be between " << min << " and "<< max << endl;
		
		//call readDouble to read a properly formatted double number
		number = readDouble(prompt);
	}			 

	return number;
}


/*Name: readInt
//Purpose: read an integer based on the prompt
//Parameters:
//	  prompt - message to display to user
//Returns: user input value
*/
int readInt(string prompt){
	int number;
	
	//attempt to read first integer input
	cout << prompt;  
	cin >> number;
	
	//did user enter a properly formatted integer number
	while (cin.fail()){
		cout << "\tImproper integer number\n";
		cin.clear();
		cin.ignore(1000, '\n');
		
		//attempt to read next integer input
		cout << "Enter number: ";  
		cin >> number;	 
	}
	
	//flush any extraneous user input in buffer, especially newline
	cin.ignore(1000, '\n');
	return number;
	
}

/*Name: readIntPos
//Purpose: read a positive integer based on the prompt
//Parameters:
//	  prompt - message to display to user
//Returns: positive user input value
*/
int readIntPos(string prompt){
	int number;
	
	//call readInt to read a properly formatted integer number
	number = readInt(prompt);
   
	while (number <= 0){
		cout <<"\tInvalid integer input - must be greater than 0" << endl;
		
		//call readInt to read a properly formatted integer number
		number = readInt(prompt);
	}
	
	return number;
}

/*Name: readIntBetween
//Purpose: read an integer between 2 integers based on the prompt
//Parameters:
	prompt - message to display to user
	min - minimum
	max - maximum
//Returns: user input value
*/
int readIntBetween(string prompt, int min, int max){
	int number;
	
	//call readInt to read a properly formatted integer number
	number = readInt(prompt);
   
	while (number < min || number > max){
		cout <<"\tInvalid integer input - must be between " << min << " and " << max << endl;
		
		//call readInt to read a properly formatted integer number
		number = readInt(prompt);
	}
	
	return number;
}
