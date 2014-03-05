//Course: 4002-208
//Author: James Haight
//Assignment: Project 2
//Purpose: "Write programs to calculate the time to transmit information over a communication line"
//Caveats: 

//include library for input and output
#include <iostream>
#include <iomanip>
using namespace std;
//Declaration of variables
int size, speed, packets, overhead, lastPack;
double secondsRaw, secondsPackaged, waste;
bool last;
int main ( )
{
	//some housekeeping
	cout << fixed << showpoint;
	
	//Input
	cout << "Input bytes to transfer: ";
	cin >> size;
	cout << "Input bps: ";
	cin >> speed;
	
	//Math
	speed = speed / 8;
	secondsRaw = double(size) / double(speed);
	if (size % 1472 != 0)
	{
		packets = (size / 1472);
		lastPack = (size % 1472) + 28;
		overhead = (packets * 28) + lastPack;
		size = ((packets) * 1500) + lastPack;
		last = true;
	}
	else
	{
		packets = size / 1472;
		lastPack = 0;
		overhead = packets * 28;
		size = packets * 1500;
		last = false;
	}
	secondsPackaged = double(size) / double(speed);
	waste = secondsPackaged - secondsRaw;
	waste = waste / secondsRaw;
	waste = waste * 100;
	
	//Output
	cout << "Time to transmit message with no overhead is " << setprecision(3) << secondsRaw << " seconds." << endl;
	cout << "Time to transmit message in packets is " << setprecision(3) << secondsPackaged << " seconds." << endl << endl;
	cout << "Packet Transmission Details" << endl << "---------------------------" << endl;
	cout << "Packet length is 1500 bytes with 28 bytes overhead." << endl;
	cout << "Number of full packets: " << packets << endl;
	if(last)
	{
		cout << "Number of data bytes in last packet: " << lastPack - 28 << endl;
	}
	cout << "Time to transmit one packet: " << setprecision(6) << 1500.0 / double(speed) << endl;
	if(last)
	{
		cout << "Time to transmit last packet: " << setprecision(6) << double(lastPack) / double(speed) << endl;
	}
	else
	{
		cout << "No partial packets sent" << endl;
	}
	cout << "Percentage overhead for packets is " << setprecision(2) << waste << "%" << endl;
	
	//Freeze DOS window until user presses a key.
	cout << endl;
	system("pause");
	//terminate program
	return 0;
} //end of main function
