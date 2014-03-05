/*Ident header
//Course: 4002-210
//Author: James Haight
*/

#include <iostream>
#include <iomanip>
#include <string>
#include "Box.h"
using namespace std;

/*Name: Box
//Purpose: creates a default box
//Parameters: none
//Returns: nothing
*/
Box::Box(){
	depth = 0.0;
	cout << "In default Box constructor" << endl;
}

/*Name: Box
//Purpose: creates a rectangle with length and width and depth
//Parameters: none
//Returns: nothing
*/
Box::Box(double length, double width, double depth):Rectangle(length,width){
	//assigns length and width to private data members
	if (depth > 0.0){  //valid dimensions
		this->depth  = depth;
	}
	else{  //invalid dimensions
		this->depth  = 0.0;
	}
	cout << "In initializing Box constructor" << endl;
}

/*Name: ~Box
//Purpose: destruct Box
//Parameters: none
//Returns: nothing
*/
Box::~Box( ){
	cout << "In Box destructor with length of " << getLength() << endl;
}

/*Name: getDepth
//Purpose: gets depth of Box
//Parameters: none
//Returns: depth of Box
*/
double Box::getDepth() const{
	return depth;
}

/*Name: calcVolume
//Purpose: calculates volume of Box
//Parameters: none
//Returns: volume of Box (width x length x length)
*/
double Box::calcVolume() const{
	return calcArea() * depth;
}

/*Name: print
//Purpose: print dimensions of Box
//Parameters: none
//Returns: none
*/
void Box::print( ) const{
	Rectangle::print();
	cout << "  Depth: " << getDepth() << endl;	
}
