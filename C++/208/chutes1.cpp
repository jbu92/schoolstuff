//Course: 4002-208
//Author: James Haight (aka group 8)
//Assignment: Chutes'n'Ladders
//Purpose:
//Caveats:

//include library for input and output
#include <iostream>
#include <math.h>
using namespace std;

int playGame();

int main ( )
{
    double ave; //average # of rolls
    int min = 100; //lowest # of rolls. init'd at 100 due to method of setting
    int max = -1; //highest # of rolls. init'd at -1 due to method of setting
    int current; //# of rolls for last game
    int total; //total # of rolls, for finding average
    int number = 10000; //# of games to play
	srand ( time(NULL) );
	cout << "Playing 10,000 games of Chutes'n'Ladders (minus the chutes'n'ladders)";
	for(int i = 0; i<number; i++){
		current = playGame();
		if(current < min) min = current;
		if(current > max) max = current;
		total += current;
	}
	ave = total / number;
	cout <<"\nMin: " << min << "\nMax: " << max << "\nAverage: " << ave;
	//Freeze DOS window until user presses a key.
	cout << endl;
	system("pause");
	//terminate program
	return 0;
} //end of main function

int playGame(){
	int roll = 0;
	int count = 0;
	int position = 0;
	while(position < 100)
	{
		roll = rand() % 6; 
		roll++; //makes one spin of a 6-sector spinner
		position += roll; //adds roll to current position
		count = count + 1; //increments count of rolls
		if(position > 100) //removes roll from position if it overshoots 100
			position -= roll;
	}
	return count;
}
