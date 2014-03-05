/* T.J. Borrelli and Rayno Niemi
 * testBox.cpp
 * 	Purpose:  test Box class
 */

#include <iostream>
#include <string>
#include <iomanip>
#include "Box.h"
using namespace std;

int main (){	
	//print options
	cout << fixed << showpoint << setprecision(2);
	
	//create a default Box
	Box rec0;
	rec0.print( );
	cout << "Volume of Box is " << rec0.calcVolume() << endl;
	cout << endl;

	//create a Box of 10.5 x 20.25 x 7.80
	Box rec(10.5, 20.25, 7.80);
	
	//print results
	rec.print( );
	cout << "Volume of Box is " << rec.calcVolume() << endl;
	
	cout << endl;
	
	return 0;  
} //end main
