#include <string>
#include "telephone.h"
class Tbook{
	private:
		Telephone rolodex[10]; //Although, your sample output was set to 9...
		int entries; //Number of entries
	public:
		Tbook(); //Default constructor
		~Tbook() {}; //Empty destructor
		void write(Telephone); //Appends rolodex.txt with the new Telephone
		void print(); //Prints entire rolodex
		Telephone lookup(string); //Looks up entry by name
		bool is_full(); //Tests whether or not the tbook is full.
		void add(Telephone); //Adds telephone entry to the rolodex
};
