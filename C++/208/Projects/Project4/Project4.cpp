//Course: 4002-208
//Author: James Haight
//Assignment: Project 4
//Purpose: GAMBLIN'!
//More seriously, for throwing this up on GitHub, Project 4 simulated a game of craps.
//Caveats: Trying more than the largest integer's number of games causes screwiness

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

//Function Prototypes
int roll();
int roll2Dice();
int readIntPos(string);
void setRand();
bool playCraps(int, bool);
bool setVerbosity();

int main(){
	//Standard housekeeping
    cout << fixed << showpoint;
	
	//Variables
	int games; //Games to be played
	bool verbose; //Whether or not to be verbose
	int wins = 0; //Number of wins
	double ave; //Average # of wins
	
	//Set random seed
	setRand();
	
	//Get number of games to play
	do{
		games = readIntPos("Enter number of games to play: ");
		if(games==0) cout << "Please play at least one game...\n";
	}while(games<=0);
	
	//Set verbosity
	verbose = setVerbosity();

	//Play some craps
	for(int i = 1; i <= games; i++){
		bool win = playCraps(i,verbose);
		if(win) wins++;
	}
	
	//Calculate average # of wins
	ave = double(wins)/double(games);
	ave = ave * 100;
	
	//Output final stats
	cout << "  Games: " << games << endl
		 << "   Wins: " << wins << endl 
		 << " Losses: " << games-wins << endl 
		 << "Average: " << setprecision(3) << ave << "%";
	
	//Freeze DOS window until user presses a key.
	cout << endl;
	system("pause");
	//terminate program
	return 0;
} //end of main function
    
/*Name: Roll
//Purpose: Roll 1 die
//Parameters: null
//Returns: int 1-6
*/
int roll(){
	int roll = 1 + rand() % 6; //generate random integer between 1 and 6
	return roll;
}

/*Name: Roll2Dice
//Purpose: Rolls 2 dice
//Parameters: null
//Returns: int 2-12
*/
int roll2Dice(){
    int a = roll();
    int b = roll();
	int roll = a + b; //rolls twice, adds them
	return roll;
}

/*Name: ReadIntPos
//Purpose: Read in 1 positive integer
//Parameters: Input prompt
//Returns: Positive integer
*/
int readIntPos(string prompt){
	int input;
	do{
		cout << prompt; //get user input
		cin >> input;
		if(input < 0) cout << "Invalid input- must be positive integer.\n"; //validate user input
	} while(input < 0);
	return input; //Returns positive integer
}

/*Name: SetRand
//Purpose: Set random seed
//Parameters: null
//Returns: void
*/
void setRand(){
	int seed = readIntPos("Input random seed (positive integer, please): ");
	if(seed == 0) seed = time(NULL); //0 handling on random seed
	srand(seed); //sets random seed based on user input
}

/*Name: PlayCraps
//Purpose: Plays 1 game of craps, prints results if so desired
//Parameters: int game- the # of the current game, bool verbose- whether or not to print output
//Returns: bool- T if win, F if false
*/
bool playCraps(int game, bool verbose){
	int roll; //Current roll
	int win = 7; //"Point" variable. 7 on first roll
	bool won; //T if win, F if loss
	if(verbose){ //Outputs each roll if user has requested verbosity
		cout << "Game " << setw(4) << right << game << ": "; //Sets up output
		roll = roll2Dice(); //First roll
		
		if(roll == 7 || roll == 11){ //Special first roll win
			cout << roll << " ";
			cout << "win\n";
			won = true;
		}
        else if(roll == 2 || roll == 3 || roll == 12){ //Special first roll loss
			cout << roll << " ";
			cout << "lose\n";
			won = false;
		} else{ //Non-Special first roll, do more rolls
			cout << roll << " ";
			win = roll; //Sets first roll as point
			
			//Roll until win/lose
			do{
				roll = roll2Dice(); //Roll
				cout << roll << " ";
			}while(roll!=win && roll!=7); //Check roll against win/loss conditions
			
			//Set "won" variable based on win/loss
			if(roll == win){
				cout << "win\n";
				won = true;
			} else{
				cout << "lose\n";
				won = false;
			}
		}
	}
	else{ //Hides rolls if user has requested no verbosity
		roll = roll2Dice(); //First roll
		if(roll == 7 || roll == 11){ //First roll special win
			won = true;
		}else if(roll == 2 || roll == 3 || roll == 12){ //First roll special loss
			won = false;
		} else{ //Non-special first roll, do more rolls
			win = roll; //Sets first roll as point
			
			//Roll until win/lose
			do{
				roll = roll2Dice(); //Roll
			}while(roll!=win && roll!=7); //Check roll against win/lose conditions
			
			//Sets won variable based on win/loss
			if(roll == win){
				won = true;
			} else{
				won = false;
			}
		}
	}
	return won; //Return win/loss status of current game
}

/*Name: SetVerbosity
//Purpose: Sets verbosity (real creative names, eh?)
//Parameters: null
//Returns: T if verbose, F if non-verbose
*/
bool setVerbosity(){
	char verbChoice; //Input to decide on verbosity
	cout << "Print results of each game? (Y/N) (default N)";
	cin >> verbChoice;
	verbChoice = toupper(verbChoice);
	
	//Return t/f based on verbChoice
	if(verbChoice == 'Y') return true;
	else return false;
}