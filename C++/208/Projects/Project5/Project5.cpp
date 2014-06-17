/*Ident header
//Course: 4002-208
//Author: Jim Haight
//Assignment: Project 5
//Purpose: Analyze temperature data
//Caveats:
*/

//Includes
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "Project5.h"
using namespace std;


int main(){
	//Housekeeping
	cout << fixed << showpoint << setprecision(2);
	
	//Variables
	string filename = "Project5File.txt"; //Default filename (because I use a different name locally, so if I put it here, it's easier to change later)
	int year; //Selected year
	int menuItem; //Selected menu item
	double data[13]; //Temperature data
	bool more = true; //More runs or not. set to false after last run
	bool quit = false; //Whether or not to break out of the menu (select a different year)
	ifstream fin;
	fin.open(filename.c_str());
	string month[13] = {"","January   ","February  ","March     ","April     ","May       ","June      ","July      ","August    ","September ","October   ","November  ","December  "}; //Months of the year, with padding for output purposes
	
	while(more){
		quit = false; //Resets quit for a new year
		
		//Get the year
		year = getYear();
		
		//Initialize array
		readMonthlyTemp(data, year, fin);

		//Display the menu and run the calculations until menu item is 5
		while(!quit){
			//Display menu
			menuItem = menu();
			
			//Run maths based on menu choice
			switch(menuItem){
				case 1:
					//Cycles through the months, outputs them and their temperature
					for(int i = 1; i <= 12; i++){
						cout << month[i] << monthlyTemp(data, i) << endl;
					}
					system("pause");
					system("cls");
					break;
				case 2:
					cout << "Average temperature for " << year << " was: " << averageTemp(data) << endl;
					system("pause");
					system("cls");
					break;
				case 3:
						cout << "The highest temperature for " << year << " was: " << highTemp(data) << endl;
						system("pause");
						system("cls");
					break;
				case 4:
					cout << "The low temperature for " << year << " was: " << lowTemp(data) << endl;
					system("pause");
					system("cls");
					break;
				case 5:
					quit = true;
					break;
			}
			system("cls"); //Clear screen after output.
		}
		
		//Check for more operations
		more = doMore();
	}

	//Displays global stats
	coldestMonth(data, fin);
	coldestYear(data, fin);
	warmestYear(data, fin);
	
	fin.close(); //Close the file when we're done with it
	//Freeze DOS window until user presses a key.
	cout << endl;
	system("pause");
	//terminate program
	return 0;
}
