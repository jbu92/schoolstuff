/*Ident header
//Course: 4002-208
//Author: Jim Haight
//Assignment: Lab8
//Purpose:
//Caveats:
*/

//Includes
#include <iostream>
#include <iomanip>
using namespace std;

//Function Prototypes

int main(){
	//Housekeeping
	cout << fixed << showpoint << setprecision(1);
	
	//Constants
	
	
	//Variables
	int classSize = 0; //Number of students

	int total = 0; //Sum of all grades
	double average; //Average grade
	int smallest = 10000; //Smallest grade
	int largest = -10000; //Largest grade	
	
	//Input class size 
	do{
		cout << "Input number of students in class: ";
		cin >> classSize;
		if(classSize <= 0) cout << "Must be more than 0 students.\n";
	}while(classSize <= 0);
	int grades[classSize]; //Grades
	
	//Initialize grade array
	for(int i = 0; i < classSize; i++) grades[i] = 0;
	
	//Read in grades
	for(int i = 0; i < classSize; i++){
		cout << "Input grade # " << i + 1 << ": ";
		cin >> grades[i];
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
