/*Ident header
//Course: 4002-210
//Author: Jim Haight
*/

//Includes
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
using namespace std;

//Function Prototypes
void fOpen(std::ifstream&, string, bool&);
void readNextLine(std::ifstream&, char[]);
bool checkValidity(char[]);

int main(){
	//Housekeeping
	cout << fixed << showpoint;
	
	//Variables
	bool fail; //File open failure check
	ifstream fin; //Input stream
	string filename;
	char password[40]; //Current password to be checked
	
	//Get filename
	cout << "Input filename: ";
	cin >> filename;
	
	//Open file
	fOpen(fin, filename, fail);
	if(fail) return 1;
	
	while(!fin.eof()){
		//Read next line
		readNextLine(fin, password);
		
		if(password[0] != NULL){ //Skips blank lines	
			//Check validity
			if(checkValidity(password))
				cout << "Password is valid\n\n";
			else
				cout << "Password is invalid\n\n";
		}
	}
	
	//End
	return 0;
}

//Function definitions

/*Name: fOpen
//Purpose: Opens file with given filename
//Parameters: ifstream object, string filename, bool fail bit
//Returns: null
*/
void fOpen(std::ifstream& fin, string filename, bool& fail){
	fin.open(filename.c_str());
	if(!fin.is_open()){
		fail = 1;
		cerr << "File failed to open";
	}
}

/*Name: readNextLine
//Purpose: Reads next line in file
//Parameters: ifstream object, char array for line to be output to
//Returns: null
*/
void readNextLine(std::ifstream& fin, char line[]){
	fin.getline( line, 40, '\n' );
}

/*Name: checkValidity
//Purpose: Checks validity of password
//Parameters: char array of password to be tried
//Returns: T if valid, else F
*/
bool checkValidity(char password[]){
	//Variables
	bool valid = 1;
	string passwordString = password;
	int capitals = 0; //Count of upper case
	int lowers = 0; //Count of lower-case
	int numbers = 0; //Count of digits
	
	cout << "Proposed password: " << password << endl;
	
	//Test password length
	if(passwordString.length() < 8){
		valid = 0;
		cout << "\tSize must be > 8.\n";
	}
	if(passwordString.length() > 15){
		valid = 0;
		cout << "\tSize must be < 15.\n";
	}
	
	//Count uppers/lowers/numbers
	for(int i = 0; i < passwordString.length(); i++){
		if(isupper(password[i])) capitals++;
		if(islower(password[i])) lowers++;
		if(isdigit(password[i])) numbers++;
	}
	
	//Check # of uppers/lowers/numbers/specials
	if(capitals + lowers + numbers < passwordString.length()){
		valid = 0;
		cout << "\tNo special characters allowed.\n";
	}
	if(capitals < 1){
		valid = 0;
		cout << "\tMust contain at least 1 capital letter.\n";
	}
	if(lowers < 1){
		valid = 0;
		cout << "\tMust contain at least 1 lower-case letter.\n";
	}
	if(numbers < 2){
		valid = 0;
		cout << "\tMust contain at least 2 numbers.\n";
	}
	
	//Check first character for letter
	if(!isalpha(password[0])){
		valid = 0;
		cout << "\tMust begin with letter.\n";
	}
	
	return valid;
}
