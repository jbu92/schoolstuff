//4002-208
//Author: James Haight
//Lab 6
//Topic: Functions
//File: area.cpp
//Purpose: This program computes the area of a triangle, given
//	the length of the three sides using the formula
//	s = 1/2(side1 + side2 + side3)
//	area = square root of (s(s-side1)(s-side2)(s-side3))

//----------------
// Include Section 
//----------------
#include <iostream>
#include <string>
#include <iomanip>
#include <math.h>
using namespace std;

//---------------------------
// Function Prototype Section
//---------------------------
double calcArea(double, double, double);
void printResults(double, double, double, double);


// ------ M A I N   P R O G R A M ------

int main (void)
{
	
	//variable declaration section
	double area  = 0.0; //area of triangle
	double side1 = 0.0; //side of triangle
	double side2 = 0.0; //side of triangle
	double side3 = 0.0; //side of triangle
	
	//print user instructions
	cout << "This program calculates the area of a triangle given" << endl;
	cout << "the length of each side of the triangle." << endl << endl;

	//get sides of triangle
	cout << "Enter length of side 1: ";
	cin >> side1;
	cout << "Enter length of side 2: ";
	cin >> side2;
	cout << "Enter length of side 3: ";
	cin >> side3;

	//compute area of triangle here
	//call your function here
	area = calcArea(side1,side2,side3);
	printResults(side1,side2,side3,area);
	
	//freeze console window
	cout << endl;
	system("pause");
	return(0);
}
//no comment

//Purpose: calculate area of a triangle given side lengths
//Parameters: side lengths
//Returns: area
double calcArea(double a, double b, double c)
{
	double s = .5*(a + b + c);
	double test = (s-a)*(s-b)*(s-c);
	if(test<0) //making sure we have an actual triangle
		test = 0;
	double area = sqrt(s*test);
	return area;
}

//Purpose: print some results?
//Parameters: side lengths and area
//Returns: nothing, just prints
void printResults(double a, double b, double c, double area)
{
	//print results
	//print 2 decimal places in sides and 4 in area
	cout << fixed << setprecision(2);
	cout << endl << endl;
	cout << "Sides of Triangle" << endl;
	cout << "-----------------" << endl;
	cout << setw(6) << a << endl; 
	cout << setw(6) << b << endl;
	cout << setw(6) << c << endl;
	cout << endl;
	cout << setprecision(4);
	cout << "Area is " << area << endl; //print 4 decimal places
}
