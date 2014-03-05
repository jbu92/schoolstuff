/*Ident header
//Course: 4002-210
//Author: James Haight
*/

#include "Rectangle.h"

class Box : public Rectangle {
	private:
		double depth;
	public:
		Box();
		Box(double,double,double);
		~Box();
		double getDepth() const;
		double calcVolume() const;
		void print() const;
	
};