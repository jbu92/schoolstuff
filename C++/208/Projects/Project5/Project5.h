/*Ident header
//Course: 4002-208
//Author: James Haight
//Assignment: Project 5
//Purpose: Analyze temperature data
//Caveats:
*/

//Includes
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

//Function Prototypes
int getYear();
void readMonthlyTemp(double data[], int, std::ifstream& fin);
int menu();
double monthlyTemp(double[], int);
double averageTemp(double[]);
double highTemp(double[]);
double lowTemp(double[]);
bool doMore();
void coldestMonth(double data[], std::ifstream& fin);
void coldestYear(double data[], std::ifstream& fin);
void warmestYear(double data[], std::ifstream& fin);
