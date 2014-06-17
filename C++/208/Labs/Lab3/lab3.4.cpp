//Course: 4002-208
//Author: Jim Haight
//Assignment:
//Purpose:
//Caveats:

//include library for input and output
#include <iostream>
using namespace std;

int main ( )
{
    while(1)
{
	double x, y;
	cout << endl << "input x and y ";
	cin >> x >> y;
	if(x > 0 && y > 0)
		cout << "point is in 1st quadrant";
	else if (x > 0 && y < 0)
		cout << "point is in 4th quadrant";
	else if (x < 0 && y < 0)
		cout << "Point is in 3rd quadrant";
	else if (x < 0 && y > 0)
		cout << "point is in 2nd quadrant";
	else if (x == 0 && y != 0)
		cout << "Point on y-axis";
	else if (y == 0 && x != 0)
		cout << "point on x-axis";
	else
		cout << "point is either (0,0) or I messed up all this iffing";
}
	//Freeze DOS window until user presses a key.
	cout << endl;
	system("pause");
	//terminate program
	return 0;
} //end of main function
    
