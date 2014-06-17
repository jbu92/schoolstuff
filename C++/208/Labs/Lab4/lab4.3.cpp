//Course: 4002-208
//Author: Jim Haight
//Assignment:
//Purpose:
//Caveats:

//include library for input and output
#include <iostream>
#include <iomanip>
using namespace std;

int main ( )
{
	cout << fixed << showpoint;
	char grade;
	int score = 0;
	int numScores = 1;
	double gpa = 0;
	int weight;
	cout << "Input ye here yon grade (A-F, Q to quit): ";
	cin >> grade;
	grade = toupper(grade);
	while(grade != 'A' && grade != 'B' && grade != 'C' && grade != 'D' && grade != 'F' && grade != 'Q')
	{
		cout << "Please input a valid grade option (A-F or Q): ";	
		cin >> grade;
		grade = toupper(grade);
	}
	while(grade != 'Q')
	{
		cout << "Input grade weight: ";
		cin >> weight;
		while(weight <= 0)
		{
			cout << "Weight must be more than 0. Try again: ";
			cin >> weight;
		}

		switch(grade)
		{
			case 'A':
				score += (4*weight);
				break;
			case 'B':
				score += (3*weight);
				break;
			case 'C':
				score += (2*weight);
				break;
			case 'D':
				score += (1*weight);
				break;
			case 'F':
			case 'Q':
				score += 0;
				break;
			default:
				score += -1;
				break;
		}
		if(grade != 'Q')
			numScores += weight;
		cout << "Input ye here yon grade (A-F, Q to quit): ";
		cin >> grade;
		grade = toupper(grade);
		while(grade != 'A' && grade != 'B' && grade != 'C' && grade != 'D' && grade != 'F' && grade != 'Q')
		{
			cout << "Please input a valid grade option (A-F or Q): ";	
			cin >> grade;
			grade = toupper(grade);
		}
	}
	if(numScores > 1)
		numScores--;
	gpa = double(score) / double(numScores);
	cout << "credits: " << numScores << endl << "score total: " << score << endl;
	cout << "GPA is: " << setprecision(2) << gpa << endl;
	//Freeze DOS window until user presses a key.
	cout << endl;
	system("pause");
	//terminate program
	return 0;
} //end of main function
    
