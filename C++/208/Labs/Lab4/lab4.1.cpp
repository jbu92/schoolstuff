//Course: 4002-208
//Author: James Haight
//Assignment:
//Purpose:
//Caveats:

//include library for input and output
#include <iostream>
using namespace std;

int main ( )
{
	char grade;
	while(true)
	{
		int score = 0;
		cout << "Input ye here yon grade: ";
		cin >> grade;
		grade = toupper(grade);
		switch(grade)
		{
			case 'A':
				score += 4;
				break;
			case 'B':
				score += 3;
				break;
			case 'C':
				score += 2;
				break;
			case 'D':
				score += 1;
				break;
			case 'F':
				score += 0;
				break;
			default:
				score += -1;
				break;
		}
		cout << "Points for grade " << grade << " is " << score << endl;
	}
	//Freeze DOS window until user presses a key.
	cout << endl;
	system("pause");
	//terminate program
	return 0;
} //end of main function
    
