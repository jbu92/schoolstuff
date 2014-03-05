//Course: 4002-208
//Author: James Haight
//Assignment: Project 3
//Purpose: "Project 3 extends Project 2 by allowing more options in the input, validating the input, and printing thetime in minutes and seconds when the time is large"
//Caveats: Incorrect input types can result in infinite loops

//include library for input and output
#include <iostream>
#include <iomanip>
using namespace std;
//Declaration of variables
int size, speed, packets, lastPack, spdInput, timeMinutes;
double timeSeconds, remainderSeconds;
bool last;
bool mins = false;
char units;
char continueOption = 'y';
static int MODEM_SPEED = 19200; //ALL IN bps, not Bps
static int COPPER_SPEED = 56000;
static int T1_SPEED = 1544000;
static int WIFI_SPEED = 22000000;
static int PACKET_SIZE = 2340;
static int HEADER_SIZE = 45;
int main ( )
{
	//some housekeeping
	cout << fixed << showpoint;
	while(continueOption == 'y' || continueOption == 'Y')
	{
		//initializing some variables because if I don't it doesn't work sometimes
		//consider it a variable reset.
		last = mins = false;
		units = '1';
		timeSeconds = remainderSeconds = size = speed = packets = lastPack = spdInput = timeMinutes = 0;
		
		//Input
		cout << "Input size of file: ";
		cin >> size;
		while(size < 1) //validation of size. must be >= 1
		{
			cout << "Try again: ";
			cin >> size;
		}
		cout << "Input units (B for bytes, K for KB, M for MB): ";
		cin >> units;
		while(units != 'B' && units != 'b' && units != 'k' && units != 'K' && units != 'M' && units != 'm') //validation of units
		{
			cout << "Try again: ";
			cin >> units;
		}
		switch(units) //modification of int size based on units provided
		{
			case 'b':
			case 'B':
				size = size;
				break; //Yes I know this is pointless, but it makes it a bit more explicit.
			case 'k':
			case 'K':
				size = size * 1024;
				break;
			case 'M':
			case 'm':
				size = size * 1048576;
				break;
		}
		cout << "Select transmission speed:\n"; //prints out menu for speed input
		cout << "1. WIFI (22,000,000 bps)\n";
		cout << "2. T1 (1,544,000 bps)\n";
		cout << "3. Copper (56,000 bps)\n";
		cout << "4. Modem (19,200 bps)\n";
		cin >> spdInput;
		while(spdInput != 1 && spdInput != 2 && spdInput != 3 && spdInput != 4) //validation of speed input (must be valid menu option)
		{
			cout << "Try again: ";
			cin >> spdInput;
		}
		switch(spdInput) //set speed based on input
		{
			case 1:
				speed = WIFI_SPEED;
				break;
			case 2:
				speed = T1_SPEED;
				break;
			case 3:
				speed = COPPER_SPEED;
				break;
			case 4:
				speed = MODEM_SPEED;
				break;
		}
		speed = speed / 8; //Conversion to Bps for math to work
		//Yes I could have done this in lines 18-21, but this is how I have chosen to do it.
		
		//Begin math
		if (size % PACKET_SIZE != 0) //Determine whether or not there is a partial last packet, calculate size accordingly
		{
			packets = (size / PACKET_SIZE);
			lastPack = (size % PACKET_SIZE) + HEADER_SIZE;
			size = ((packets) * (PACKET_SIZE + HEADER_SIZE)) + lastPack;
			last = true;
		}
		else
		{
			packets = size / PACKET_SIZE;
			lastPack = 0;
			size = packets * (PACKET_SIZE + HEADER_SIZE);
			last = false;
		}
		timeSeconds = double(size) / double(speed); //Calculate transmission time
		if(timeSeconds >= 60) //Check size of time for minute conversion, calculate time accordingly
		{
			timeMinutes = timeSeconds / 60;
			remainderSeconds = timeSeconds - (timeMinutes * 60); //Because modulo doesn't work right
			mins = true;
		}

		//Begin Output
		cout << "\n\nSpeed selected was " << speed * 8 << " bps.\n";
		if(!last)
		{
			cout << "Message size is " << size - (packets * HEADER_SIZE) << " bytes.\n";
		}
		else
		{
			cout << "Message size is " << size - ((packets + 1) * HEADER_SIZE) << " bytes.\n";
		}
		cout << "Packet length is " << PACKET_SIZE + HEADER_SIZE << " bytes with " << HEADER_SIZE << " bytes of overhead.\n";
		cout << "Number of full packets: " << packets << endl;
		if(last)
		{
			cout << "Size of last packet: " << lastPack - HEADER_SIZE << endl;
		}
		else
		{
			cout << "No partial last packet.\n";
		}
		if(mins) //Output for minuted time
		{
			cout << "Time to transmit file is " << timeMinutes << " minutes and " << setprecision(5) << remainderSeconds << " seconds.\n";
		}
		else //Output for 0 min, just seconds
		{
			cout << "Time to transmit file is " << setprecision(5) << timeSeconds << " seconds.\n";
		}
		cout << "Hath ye more datas to input? (y/n)"; //Shall we continue?
		cin >> continueOption;
	} //Note the lack of system pause- program terminates when user decides not to continue. Simply for usability so users do not need to hit enter twice.
	  //Yes some of the code could be cleaned up with a few tweaks, but hey it works.
} //end of main function
