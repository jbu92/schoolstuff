/*Ident header
//Course: 4002-210
//Author: James Haight
*/

//Includes
#include "tbook.h"
#include <iostream>
#include <string>
using namespace std;

//Function Prototypes
bool menu(Tbook);
void lookup(Tbook);
void add(Tbook);
void print(Tbook);

int main(){
	//Housekeeping
	cout << fixed << showpoint;
	
	//Variables
	Tbook tbook;
	bool more = true;
	
	//Run menu until option 4 selected
	while(more){
		more = menu(tbook);
	}
	
	//terminate program
	return 0;
}

//Function definitions

/*Name: Menu
//Purpose: Present user with menu
//Parameters: Tbook
//Returns: none
*/
bool menu(Tbook tbook){
	int choice;
	
	//Print ye yon menu
	cout << "Please select an option:\n 1. Lookup\n 2. Add\n 3. Print all numbers\n 4. Quit\nEnter option: ";
	cin >> choice;
	
	//Execute selected choice
	switch(choice){
		case 1:
			lookup(tbook);
			break;
		case 2:
			add(tbook);
			break;
		case 3:
			print(tbook);
			break;
		case 4:
			return false;
	}
	return true;
}

/*Name: Lookup
//Purpose: Look up a name in the Tbook
//Parameters: Tbook
//Returns: nada
*/
void lookup(Tbook tbook){
	string name;
	
	//Reset input buffer completely
	cin.clear();
	cin.sync();
	
	//Get input of name to look for
	cout << "Enter name to look up (must be EXACT match): ";
	getline(cin, name);
	
	//Look for name
	Telephone result = tbook.lookup(name);
	if(result.getName() != name){
		cout << "\nNot found in rolodex\n";
	}
	else
		result.print();
}

/*Name: Add
//Purpose: Add an entry to the Tbook
//Parameters: Tbook
//Returns: Nothing
*/
void add(Tbook tbook){
	string newName, newAreaCode, newNumber;
	
	//Reset input buffer completely
	cin.clear();
	cin.sync();
	
	//Get input
	cout << "Enter name for new entry: ";
	getline(cin, newName);
	cout << "Enter area code for " << newName << ": ";
	cin >> newAreaCode;
	cout << "Enter number for " << newName << ": ";
	cin >> newNumber;
	
	//Use input
	Telephone newPhone(newName, newAreaCode, newNumber);
	tbook.add(newPhone);
}

/*Name: Print
//Purpose: Dump the database
//Parameters: Tbook
//Returns: Void
*/
void print(Tbook tbook){
	tbook.print(); //Run ye yon printification function
}
