/*
Course: 4002-208
Author: Jim Haight
Assignment: Project1
Purpose: Calculate annual fuel costs
Caveats:
*/
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
//Declaration of variables
int mpgHiway, mpgTown, miles, percentTown;
float total, cityVol, hiwayVol, used, milesHiway, milesTown, PRICE;
string car;
//Hey look, the main 
int main ()
{
    //Set output to decimal notation instead of scientific
    cout << fixed << showpoint;
    //Here be the initialization of PPG
    PRICE = 3.73;
    //Variable acquisition section
    cout << "Enter manufacturer and model of car: ";
    getline (cin, car);
    cout << "Enter EPA estimate of city miles per gallon: ";
    cin >> mpgTown;
    cout << "Enter EPA estimate of highway miles per gallon: ";
    cin >> mpgHiway;
    cout << "Enter number of miles driven per year: ";
    cin >> miles;
    cout << "Enter percentage of miles driven in city: ";
    cin >> percentTown;
    //Some maths to make some of the variables right
    milesTown = miles * percentTown / 100;
    milesHiway = miles - milesTown;
    cityVol= milesTown / mpgTown;
    hiwayVol = milesHiway / mpgHiway;
    total = ( hiwayVol + cityVol ) * PRICE;
    //I don't know why you said in the "hey read this stuffs here and do this this way" thing to do it this way... there's easier ways to do the math. but it's the night of the 6th and I'm bored so I'm just going to do it how you say to...
    cout << setprecision(2) << "Annual fuel costs of " << car << " estimated at $" << total << endl;
    cout << "Based on the following factors:" << endl;
    cout << "   Cost of gas is $" << PRICE << " per gallon" << endl;
    cout << "   Fuel economy ratings are " << mpgTown << "/" << mpgHiway << endl;
    cout << "   Gallons used are " << hiwayVol + cityVol << endl << endl;
    system("Pause");
    return 0;
}
