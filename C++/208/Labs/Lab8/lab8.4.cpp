/*Ident header
//Course: 4002-208
//Author: James Haight
//Assignment: Lab8
//Purpose:
//Caveats:
*/

//Includes
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

//Function Prototypes

int main(){
	//Housekeeping
	cout << fixed << showpoint << setprecision(1);
	
	//Constants
	
	//Variables
	int classSize = -1; //Number of students
	int grades[classSize]; //Grades
	int total = 0; //Sum of all grades
	double average; //Average grade
	int smallest = 10000; //Smallest grade
	int largest = -10000; //Largest grade
	string filename; //File name
	ifstream fin;
	
	cout << "Input file name: ";
	getline(cin,filename);
	
	fin.open(filename.c_str());
	
	if(!fin.is_open()){
		cout << "AH CAINT FIND YO FILE!!! EXITING, BRAH!";
		system("exit");
	}
	
	//Input class size
	fin >> classSize;
	
	//Initialize grade array
	for(int i = 0; i < classSize; i++) grades[i] = 0;
	
	//Read in grades
	for(int i = 0; i < classSize; i++){
		fin >> grades[i];
		if(grades[i]<smallest) smallest = grades[i];
		if(grades[i]>largest) largest = grades[i];
	}
	
	
	//Sum grades
	for(int i = 0; i < classSize; i++) total+= grades[i];
	
	//Calculate average
	average = double(total)/double(classSize);
	
	//Output average, max, min
	cout << "Average grade is: " << average << endl;
	cout << "Max: " << largest << endl;
	cout << "Min: " << smallest << endl;
	
	//Output grades
	cout << "List of grades:\n";
	for(int i = 0; i < classSize; i++){
		cout << grades[i] << " ";
		if(i%5==4) cout << endl;
	}
	
	//Freeze DOS window until user presses a key.
	cout << endl;
	fin.close();
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
