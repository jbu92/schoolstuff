//*********************************************************************
// FILE NAME:  washer.cpp
// AUTHOR: Jim Haight	              <--ENTER YOUR NAME HERE!
// Lab 1
// Exercise 1
// DESCRIPTION: Compute and print the area of a washer to
//              screen after prompting the user for the inner and
//              outer diameters of the washer
//*********************************************************************

#include <iostream>
using namespace std;
//using std::cin;
//using std::cout;
//using std::endl;

int main()
{
    //constant section
    const double PI = 3.141592653589793;
    
    //variable declarations
    double diameter;         //user's diameter input
    double outerArea;       //area of whole washer's circle
    double innerArea;       //area of washer's hole
    double washerArea;      //difference of the 2 areas
	double radius;			//defining radius
     
    //get washer's outer diameter value
    cout << "Enter the outer diameter of the washer in inches: ";
    cin >> diameter;
    radius = diameter/2;
    //calculate outer area using A = PI x r^2
    outerArea = PI * radius * radius ;
    
    //get washer's inner diameter value
    cout << "\nEnter the inner diameter of the washer in inches: ";
    cin >> diameter;
    radius = diameter/2;
    //calculate inner area using A = PI x r^2
    innerArea = PI * radius * radius ;
    
    //take difference of the 2 areas to get washer area
    washerArea = outerArea - innerArea;
    
    //print area to screen
    cout << "\n The area of the washer is: " << washerArea << " square inches." << endl << endl;
    
    //freeze output window
    cout << endl;
    system("pause");
    return (0);
}
