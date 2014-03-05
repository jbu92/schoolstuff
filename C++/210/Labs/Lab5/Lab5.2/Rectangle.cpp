/* T.J. Borrelli Rayno Niemi
 * File: Rectangle.cpp
 * Purpose: Implementation of Rectangle class
 */

#include <iostream>
#include <iomanip>
#include <string>
#include "Rectangle.h"
using namespace std;

//------------------------------------------
//Name: Rectangle
//Purpose: creates a default rectangle
//Parameters: none
//Returns: nothing
//------------------------------------------
Rectangle::Rectangle( )
{
    length = 0.0;
    width  = 0.0;
    cout << "In default Rectangle constructor" << endl;
}

//------------------------------------------
//Name: Rectangle
//Purpose: creates a rectangle with length and width
//Parameters: 
//  length - length of rectangle
//  width - width of rectangle
//Returns: nothing
//------------------------------------------
Rectangle::Rectangle(double length, double width)
{
     //assigns length and width to private data members
     if (length > 0.0 && width > 0.0)
     {  //valid dimensions
         this->length = length;
         this->width  = width;
     }
     else
     {  //invalid dimensions
        this->length = 0.0;
        this->width  = 0.0;
     }
     cout << "In initializing Rectangle constructor" << endl;
}


//------------------------------------------ 
//Name: ~Rectangle
//Purpose: destruct rectangle
//Parameters: none
//Returns: nothing
//------------------------------------------
Rectangle::~Rectangle( )
{
    cout << "In Rectangle destructor with length of " 
         << getLength() << endl;
}

//------------------------------------------ 
//Name: getLength
//Purpose: gets length of rectangle
//Parameters: none
//Returns: length of rectangle
//------------------------------------------
double Rectangle::getLength() const
{
    return length;
}
  

//------------------------------------------    
//Name: getWidth
//Purpose: gets width of rectangle
//Parameters: none
//Returns: width of rectangle
//------------------------------------------
double Rectangle::getWidth() const
{
    return width;
}


//------------------------------------------    
//Name: calcArea
//Purpose: calculates area of rectangle
//Parameters: none
//Returns: area of rectangle (width x length)
//------------------------------------------
double Rectangle::calcArea() const
{
     return length * width;
}

//------------------------------------------
//Name: print
//Purpose: print dimensions of rectangle
//Parameters: none
//Returns: none
//------------------------------------------
void Rectangle::print( ) const
{
    cout << "Dimensions"<< endl
         << "  Length: " << getLength() << endl
         << "  Width:  " << getWidth()  << endl;    
}
