/*Ident header
//Course: 4002-210
//Author: Jim Haight
*/

//Includes
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
using namespace std;

//Function Prototypes
void openFile(std::ifstream&);

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
	//string filename;
	ifstream fin;
	
	/*cout << "Input filename: ";
	cin >> filename;
	fin.open(filename.c_str());
	if(!fin.is_open()){
		cout << "Unable to open file.\n";
		system("pause");
		return 0;
	}
	*/
	openFile(fin);
	while(!fin.eof()){
		getline(fin, input);
		inputC = new char [input.size()+1];
		strcpy(inputC, input.c_str());
		commas = 0;
		
		for(int i = 0; i<input.length(); i++){
			if(inputC[i]==',') commas++;
		}
		
		if(commas == 4){
			cout << "\n\nOriginal string <" << input << ">\n----------\n";
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
			
			if(zip.length() != 5 && zip.length() != 10) cout << "Zip is invalid\n";
			else cout << "Zip is valid\n";
		}
		else{
			cout << "Invalid input\n";
			system("pause");
		}
		
	}
	
	fin.close();
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
void openFile(std::ifstream& fin){
	string filename;
	do{
		cout << "Input filename: ";
		cin >> filename;
		fin.open(filename.c_str());
		if(!fin.is_open()){
			cout << "Unable to open file.\n";
		}
		fin.clear();
	} while(!fin.is_open());
}
