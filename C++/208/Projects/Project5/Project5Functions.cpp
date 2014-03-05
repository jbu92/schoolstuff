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

//Function definitions
/*Name: getYear
//Purpose: Gets year from user
//Parameters: none
//Returns: int year
*/
int getYear(){
	int year;
	do{ //Asks for year
		cout << "Please enter a year between 1940 and 2010: ";
		cin >> year;
		
		//Validates input
		if(year > 2010 || year < 1940)
			cout << "Invalid input, must be between 1940 and 2010" << endl;
	}while(year > 2010 || year < 1940);
	
	//Returns input
	return year;
}

/*Name: readMonthlyTemp
//Purpose: Reads the monthly temperatures into the data array
//Parameters: Data array, year, and the ifstream
//Returns: none
*/
void readMonthlyTemp(double data[], int year, std::ifstream& fin){
	fin.seekg (0, ios::beg); //Resets fin to the beginning of the file
	do{ //Finds the right line
		fin >> data[0];
	}while(data[0] != year);
	for(int i = 1; i <= 12; i++){ //reads the rest of that line into the data array
		fin >> data[i];
	}
}

/*Name: Menu
//Purpose: Displays a menu, returns the selection
//Parameters: none
//Returns: int menu selection
*/
int menu(){
	int input;
	do{ //Displays menu
		cout << "1. Display monthly temperature for all months in the year" << endl 
			 << "2. Calculate average temperature for the entire year" << endl
			 << "3. Display highest monthly temperature for the year" << endl
			 << "4. Display lowest monthly temperature for the year" << endl
			 << "5. Quit" << endl
			 << "Please enter selection: ";
		cin >> input;
		
		//Validates input
		if(input > 5 || input < 0)
			cout << "Please make a selection from the menu: 1-5." << endl;
	}while(input > 5 || input < 0);
	
	system("cls");
	//Returns input
	return input;
}

/*Name: monthlyTemp
//Purpose: Displays the monthly temperature for all months in the year
//Parameters: Data array, current month (1-12)
//Returns: Temperature for given month
*/
double monthlyTemp(double data[], int month){
	return data[month];
}

/*Name: averageTemp
//Purpose: Displays the average temperature for the year
//Parameters: Data array
//Returns: Average temperature
*/
double averageTemp(double data[]){
	double sum = 0; //Sum of temperatures in all months of year
	double ave; //Average temperature throughout year
	
	//Cycle through months
	for(int i = 1; i <= 12; i++){
		sum += data[i]; //Add current month to total
	}
	
	//Calculate and return average
	ave = sum / 12;
	return ave;
}

/*Name: highTemp
//Purpose: Displays the high temperature for the year
//Parameters: Data array
//Returns: Low temperature
*/
double highTemp(double data[]){
	double high = 0; //Current high temperature. Initialized low.
	
	//Cycle through the months
	for(int i = 1; i <= 12; i++){
		if(data[i] > high) high=data[i]; //Decide if current month is higher than the current high.
	}
	
	//Return high
	return high;

}

/*Name: lowTemp
//Purpose: Displays the low temperature for the year
//Parameters: Data array
//Returns: Low temperature
*/
double lowTemp(double data[]){
	double low = 1000; //Current lowest temperature. Initialized high.
	
	for(int i = 1; i <= 12; i++){ //Cycle through each month
		if(data[i] < low) //Decide if month is lower than current lowest
			low = data[i];
	}
	
	return low;
	
}

/*Name: doMore
//Purpose: Asks user whether or not to continue
//Parameters: none
//Returns: bool- T if more runs, F if no more runs
*/
bool doMore(){
	char choice;
	do{
		//Take input
		cout << "Would you like to continue? (Y/N) ";
		cin >> choice;
		
		//Validate input
		choice = toupper(choice);
		if(choice != 'Y' && choice != 'N')
			cout << "Invalid choice, please select y or n\n";
	}while(choice != 'Y' && choice != 'N');
	
	//Return T/F based on input
	if(choice == 'Y') return true;
	else return false;
}

/*Name: coldestMonth
//Purpose: Determines and outputs coldest month overall
//Parameters: Data array, fin
//Returns: none
*/
void coldestMonth(double data[], std::ifstream& fin){
	int monthLow; //Lowest month
	int yearLowMonth; //Year the lowest month is in
	double lowMonth = 1000; //Temp of lowest month, initialized high to make it easy
	
	for(int year = 1940; year < 2010; year++){ //Cycles through years
		//Setup the data array for current year
		readMonthlyTemp(data, year, fin);
		for(int month = 1; month <= 12; month++){ //Cycles through months
			//Decide if month is lowest
			if(data[month] < lowMonth){ 
				lowMonth = data[month];
				monthLow = month;
				yearLowMonth = year;
			}
		}
	}
	
	//Output
	cout << "Month " << monthLow << " of " << yearLowMonth << " had the lowest average temperature, which was " << lowMonth << endl;
}

/*Name: coldestYear
//Purpose: Determines and outputs coldest year
//Parameters: Data array, fin
//Returns: none
*/
void coldestYear(double data[], std::ifstream& fin){
	int yearLow; //Coldest year
	double lowYear = 10000; //Temperature thereof
	
	for(int year = 1940; year < 2010; year++){
		//Setup the data array for current year
		readMonthlyTemp(data, year, fin);
		
		//Decide if year has lowest average
		if(averageTemp(data) < lowYear){ 
			yearLow = year;
			lowYear = averageTemp(data);
		}
	}
	
	//Output
	cout << yearLow << " had the lowest average temperature, which was " << lowYear << endl;
}

/*Name: warmestYear
//Purpose: Determines and outputs warmest year
//Parameters: Data array, fin
//Returns: none
*/
void warmestYear(double data[], std::ifstream& fin){
	int yearHigh; //Highest year
	double highYear = -1; //Current highest temperature
	for(int year = 1940; year < 2010; year++){ //Cycle through the years
		//Setup the data array for current year
		readMonthlyTemp(data, year, fin);
		
		//Decide if year has highest average
		if(averageTemp(data) > highYear){ 
			yearHigh = year;
			highYear = averageTemp(data);
		}
	}
	
	//Output
	cout << yearHigh << " had the highest average temperature, which was " << highYear << endl;
}
