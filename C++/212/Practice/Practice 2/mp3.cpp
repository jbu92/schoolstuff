//IDENT HEADER
//NAME: Jim Haight
//CLASS: 4050-212
//Purpose: Modifies mp3 track info

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//get rid of zero
//CAST ZERO TRACK GENRE AS INT
struct metaData{
	char tag[4], title[31], artist[31], album[31], year[5], comment[29], zero[2], track[2], genre[2];
};

//Function prototypes
bool readFile(string filename, metaData &currFile);
void writeFile(string filename, metaData &currFile);
void print(metaData &currFile);
void changeData(metaData &currFile);

int main () {
	string filename;
	string yesno; //Would you like to change or not?
	metaData thisFile;
	while(filename != "exit"){
		cout << "Please enter the filename of the file you wish to change ('exit' to quit): ";
		cin >> filename;
		if(filename == "exit")
			break;
		if(!readFile(filename, thisFile)){
			cout << "File not found.\n";
		}
		else{
			print(thisFile);
			cout << "Would you like to change this information? (yes/no) ";
			cin >> yesno;
			if(yesno == "yes"){
				changeData(thisFile);
				writeFile(filename, thisFile);
				cout << "The changes have been written.";
			}
			else{
				cout << "No changes made. Goodbye." << endl;
			}
		}
	}
	
	system("pause");
	return 0;
}

bool readFile(string filename, metaData &currFile){
	FILE * pFile;
	pFile = fopen(filename.c_str(), "r");
	if(pFile == NULL){
		return false;
	}
	
	//Get to the end, go back 128B
	fseek (pFile, -128, SEEK_END);
	
	//read in each field
	fgets( currFile.tag, 4, pFile);
	fgets( currFile.title, 31, pFile);
	fgets( currFile.artist, 31, pFile);
	fgets( currFile.album, 31, pFile);
	fgets( currFile.year, 5, pFile);
	fgets( currFile.comment, 29, pFile);
	fgets( currFile.zero, 2, pFile);
	fgets( currFile.track, 2, pFile);
	fgets( currFile.genre, 2, pFile);
	
	fclose(pFile);
	return true;
}

void writeFile(string filename, metaData &currFile){
	FILE * pFile;
	pFile = fopen(filename.c_str(), "r+");
	char nulls [128];
	
	//Clear out that 128B
	for(int i = 0; i< 128; i++){
		nulls[i] = '\0';
	}
	fseek (pFile, -128, SEEK_END);
	fputs(nulls,pFile);
	
	
	
	//Get to the end, go back 128B
	//Start writing
	fseek (pFile, -128, SEEK_END);
	fputs(currFile.tag,pFile);
	fseek (pFile, -125, SEEK_END);
	fputs(currFile.title,pFile);
	fseek (pFile, -95, SEEK_END);
	fputs(currFile.artist,pFile);
	fseek (pFile, -65, SEEK_END);
	fputs(currFile.album,pFile);
	fseek (pFile, -35, SEEK_END);
	fputs(currFile.year,pFile);
	fseek (pFile, -31, SEEK_END);
	fputs(currFile.comment,pFile);
	fseek (pFile, -3, SEEK_END);
	fputs(currFile.zero,pFile);
	fseek (pFile, -2, SEEK_END);
	fputs(currFile.track,pFile);
	fseek (pFile, -1, SEEK_END);
	fputs(currFile.genre,pFile);
	fseek (pFile, -0, SEEK_END);
	
	fclose(pFile);
}

void print(metaData &currFile){
	cout << "The current metadata is as follows:\n";
	cout << "Tag: " << currFile.tag << endl
		 << "Title: " << currFile.title << endl
		 << "Artist: " << currFile.artist << endl
		 << "Album: " << currFile.album << endl
		 << "Year: " << currFile.year << endl
		 << "Comment: " << currFile.comment << endl
		 << "Zero: " << (int)currFile.zero[0] << endl
		 << "Track: " << (int)currFile.track[0] << endl
		 << "Genre: " << (int)currFile.genre[0] << endl;
}

void changeData(metaData &currFile){
	int choice;   //Menu input
	string line; //for the inputs
	int newInt; //for the int inputs
	do{
		print(currFile);
		cout << "1. Title" << endl
		 << "2. Artist" << endl
		 << "3. Album" << endl
		 << "4. Year" << endl
		 << "5. Comment" << endl
		 << "6. Zero" << endl
		 << "7. Track" << endl
		 << "8. Genre" << endl
		 << "0. Done" << endl; 
		cout << "Please enter the number of the item you would like to change (0 to exit): ";
		cin >> choice;
		cin.ignore(1000, '\n');
		
		switch(choice){
			case 1:
				cout << "Enter new Title value: ";
				//fgets(currFile.title, 30, stdin);
				getline(cin, line);
				strncpy(currFile.title, line.c_str(), 30);
				break;
			case 2:
				cout << "Enter the new Artist value: ";
				//fgets(currFile.artist, 30, stdin);
				getline(cin, line);
				strncpy(currFile.artist, line.c_str(), 30);
				break;
			case 3:
				cout << "Enter the new Album value: ";
				//fgets(currFile.album, 30, stdin);
				getline(cin, line);
				strncpy(currFile.album, line.c_str(), 30);
				break;
			case 4:
				cout << "Enter the new Year value: ";
				//fgets(currFile.year, 4, stdin);
				getline(cin, line);
				strncpy(currFile.year, line.c_str(), 4);
				break;
			case 5:
				cout << "Enter the new Comment value: ";
				//fgets(currFile.comment, 28, stdin);
				getline(cin, line);
				strncpy(currFile.comment, line.c_str(), 28);
				break;
			case 6:
				cout << "Enter the new Zero value: ";
				//fgets(currFile.zero, 1, stdin);
				cin >> newInt;
				currFile.zero[0] = (char)newInt;
				currFile.zero[1] = '\0';
				break;
			case 7:
				cout << "Enter the new Track value: ";
				//fgets(currFile.track, 1, stdin);
				cin >> newInt;
				currFile.track[0] = (char)newInt;
				currFile.track[1] = '\0';
				break;
			case 8:
				cout << "Enter the new Genre value: ";
				//fgets(currFile.genre, 1, stdin);
				cin >> newInt;
				currFile.track[0] = (char)newInt;
				currFile.track[1] = '\0';
				break;
		}
		//cin.ignore(10000, '\n'); //Overflow protection
	} while(choice != 0);
}
