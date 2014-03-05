/* T.J. Borrelli and  Rayno Niemi
 * File: Box.h
 * Purpose:  Declaration of Box class
 *		   Purposely stripped down to a minimum
 */

#ifndef BOX_H
#define BOX_H

class Box{
private:
	double length;  //length of Box
	double width;   //width  of Box
	double depth;	//depth of Box

public: 
	//constructors
	Box( );
	Box(double length, double width, double depth);
	
	//destructor
	~Box( );
	
	//accessors
	double getLength() const;   
	double getWidth() const;
	double getDepth() const;
	
	//other
	double calcVolume() const;
	void   print( ) const;
};

#endif
