/* T.J. Borrelli and  Rayno Niemi
 * File: Rectangle.h
 * Purpose:  Declaration of Rectangle class
 *           Purposely stripped down to a minimum
 */

#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle
{
private:
    double length;  //length of rectangle
    double width;   //width  of rectangle

public: 
    //constructors
    Rectangle( );
    Rectangle(double length, double width);
    
    //destructor
    ~Rectangle( );
    
    //accessors
    double getLength() const;   
    double getWidth() const;
    
    //other
    double calcArea() const;
    void   print( ) const;
};

#endif
