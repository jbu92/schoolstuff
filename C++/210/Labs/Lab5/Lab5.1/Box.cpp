/* T.J. Borrelli Rayno Niemi
 * File: Box.cpp
 * Purpose: Implementation of Box class
 */

#include <iostream>
#include <iomanip>
#include <string>
#include "Box.h"
using namespace std;

/*Name: Box
//Purpose: creates a default Box
//Parameters: none
//Returns: nothing
*/
Box::Box( ){
	length = 0.0;
	width  = 0.0;
	depth = 0.0;
	cout << "In default Box constructor" << endl;
}

/*Name: Box
//Purpose: creates a Box with length and width
//Parameters: 
//  length - length of Box
//  width - width of Box
//Returns: nothing
*/
Box::Box(double length, double width, double depth){
	//assigns length and width to private data members
	if (length > 0.0 && width > 0.0 && depth > 0.0){  //valid dimensions
		this->length = length;
		this->width  = width;
		this->depth  = depth;
	}
	else{  //invalid dimensions
		this->length = 0.0;
		this->width  = 0.0;
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

/*Name: getLength
//Purpose: gets length of Box
//Parameters: none
//Returns: length of Box
*/
double Box::getLength() const{
	return length;
}
  

/*Name: getWidth
//Purpose: gets width of Box
//Parameters: none
//Returns: width of Box
*/
double Box::getWidth() const{
	return width;
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
	return length * width * depth;
}

/*Name: print
//Purpose: print dimensions of Box
//Parameters: none
//Returns: none
*/
void Box::print( ) const{
	cout << "Dimensions"<< endl << "  Length: " << getLength() << endl << "  Width:  " << getWidth()   << endl << "  Depth: " << getDepth() << endl;	
}
