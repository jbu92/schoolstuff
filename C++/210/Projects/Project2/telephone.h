#include <string>
using namespace std;
class Telephone{
        private:
			string name, areaCode, number;
		public:
			Telephone(); //Look ma, I'm a constructor
			Telephone(string,string,string); // See above
			void print(); //Prints out Telephone entry
			string getName(); //Returns name
			int getAreaCode(); //Returns area code
			int getNumber(); //Returns number
			void setName(string); //Sets name
			bool setAreaCode(string); //Sets area code
			bool setNumber(string); //Sets number
};
