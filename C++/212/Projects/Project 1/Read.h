/*Ident header
//Course: 4002-212
//Author: Jim Haight
//Assignment: Project 1
*/
#include <fstream>
#include <string>
using namespace std;
class Read{
	private:
		ifstream fin;
		string filename;
		int filesize;
		string line;
	public:
		Read(string newFileName, unsigned int *data);
		void getData(unsigned int *dataStorage);
		int getFileSize();
};
