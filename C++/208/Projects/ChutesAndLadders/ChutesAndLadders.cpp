/*Ident header
//Course: 4002-208
//Author: Jim Haight & team
//Assignment: Chutes and Ladders
//Purpose: Estimate time to play chutes and ladders
//Caveats: Doesn't work so well for huge numbers of games, due to variable rollover (really peeved me before I figured that out...)
*/

//Includes
#include <iostream>
#include <math.h>
using namespace std;

//Function Prototypes
int playGame(int array[]);
double calcStats(int games, double average, int sigmaXiSquare);

int main(){
	//Housekeeping
	cout << fixed << showpoint;
	srand(time(NULL));
	
	//Variables
	int array[101]; //Board spaces
	int position = 0; //Current position
	int total = 0; //Cumulative roll count for purposes of calculating average
	double average; //Average number of rolls per game
	int games = 0; //Number of games played, for purposes of calculating average
	double sd; //Standard deviation
	int xSubISquare = 0; //X sub i, squared, for purposes of stats
	int sumXI = 0; //Cumulative sum of X sub i squared
	int currGame; //Number of rolls of current game (x sub i)
	double timeLow; //Low time estimate
	double timeHigh; //High time estimate
	int min = 1000; //Minimum # of rolls
	int max = -1; //Maximum # of rolls
	
	//Constants
	const int ROLLS_PER_MIN = 4; //15 sec/roll = 4 roll/min
	
	//Initialize board with values of the space (i.e. first location is 1, 10th is 10, etc.)
	for(int i = 0; i < 101; i++){
		array[i] = i;
	}

	//Index value is the start of the ladder/slide, stored value is the index value of the endpoint of the ladder/slide
	//Set the ladders
	array[1]  = 38;
	array[4]  = 14;
	array[9]  = 31;
	array[21] = 42;
    array[28] = 84;
	array[36] = 44;
	array[51] = 67;
	array[71] = 91;
	array[80] = 100;
	
	//Set the slides
	array[98] = 78;
	array[95] = 75;
	array[93] = 73;
	array[87] = 24;
	array[64] = 60;
	array[62] = 19;
	array[56] = 53;
	array[49] = 11;
	array[47] = 26;
	array[16] = 06;
	
	//Game logic
	for(int i = 0; i < 100000; i++){ //Plays 100,000 games
		currGame = playGame(array);
		total += currGame; //Increases total rolls by number of rolls of the games
		xSubISquare = currGame * currGame; //Square of x sub i
		sumXI += xSubISquare; //Adds x sub i squared to the running sum thereof
		games++;
		//Calc min/max
		if(currGame < min) min = currGame;
		if(currGame > max) max = currGame;
	}
	//Calculate basic stats
	average = double(total)/double(games); //Calculates average # of rolls
	
	//Calculate advanced stats
	sd = calcStats(games, average, sumXI);
	
	//Output stats
	cout << "100,000 games simulated\n";
	cout << "Minimum: " << min << endl;
	cout << "Maximum: " << max << endl;
	cout << "Average: " << average << endl;
	cout << "Standard deviation: " << sd << endl;
	cout << "\n";
	
	//Calculates and outputs time estimate
	timeLow = (average - sd) / ROLLS_PER_MIN;
	timeHigh = (average + sd) / ROLLS_PER_MIN;
	cout << "Based on this, the game should take between " << timeLow << " minutes and " << timeHigh << " minutes." << endl;
	
	//Freeze DOS window until user presses a key.
	cout << endl;
	system("pause");
	//terminate program
	return 0;
}

//Function definitions
/*Name: playGame
//Purpose: Plays chutes and ladders
//Parameters: array of spaces
//Returns: number of rolls to win
*/
int playGame(int array[]){
	//Constants
	const int FACES = 6; //number of faces
	const int LOW_FACE = 1; //low face
	
	//Variables
	int roll; //current roll
	int position = 0; //current position
	int count = 0; //total rolls
	int newPosition; //new position
	
	do{ //plays to 100
		roll = LOW_FACE + (rand( ) % FACES); //DO A BARREL ROLL!!! er uhh... I mean... roll the die (spin the spinner)
		newPosition = position + roll; //set the possible new position as the current position pluss the roll
		if(newPosition <= 100) //Make sure you can move to the next spot
    		position = array[newPosition];
		count++; //increment number of rolls
	}while(position < 100);
	
	return count;
}

/*Name: calcStats
//Purpose: Calculates standard deviation and estimated time
//Parameters: 
	int games- number of games
	double average- average number of rolls per game
	int sigmaXiSquare- sum of squares of x sub i
//Returns: Standard deviation
*/
double calcStats(int games, double average, int sigmaXiSquare){
	double sd; //Standard deviation
	double meanXsquare; //Average x squared
	
	meanXsquare = average * average; //average squared
	
	//Calculate standard deviation
	sd = sqrt( (1/double(games)) * sigmaXiSquare - meanXsquare);
	
	return sd;
}
