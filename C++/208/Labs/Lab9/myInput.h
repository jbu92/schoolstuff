//Course: 4002-208
//Author: Jim Haight
//Derivative of: Rayno Niemi
//Header file for myInput.h

#include <string>
using namespace std;

//double input function prototypes
double readDouble(string prompt);
double readDoublePos(string prompt);
double readDoubleBetween(string prompt, double min, double max);

//integer input function prototypes
int readInt(string prompt);
int readIntPos(string prompt);
int readIntBetween(string prompt, int min, int max);
