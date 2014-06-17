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
	
	//Variables
	int grades[6]; //Grades
	int total = 0; //Sum of all grades
	double average; //Average grade
	
	//Initialize grade array
	for(int i = 0; i < 6; i++) grades[i] = 0;
	
	//Read in grades
	for(int i = 0; i < 6; i++){
		cout << "Input grade # " << i + 1 << ": ";
		cin >> grades[i];
	}
	
	//Sum grades
	for(int i = 0; i < 6; i++) total+= grades[i];
	
	//Calculate average
	average = double(total)/6.0;
	
	//Output average
	cout << "Average grade is: " << average << endl << endl;
	
	//Output grades
	cout << "List of grades:\n";
	for(int i = 0; i < 6; i++) cout << grades[i] << " ";

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
