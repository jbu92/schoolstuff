#include "Supply.h"
#include <string>
using namespace std;

const int C_BLACK = 1;
const int C_BLUE = 2;
const int C_RED = 3;
const int NA = 0;
class Pen : public Supply{
	private:
		int penColor;
		int inkColor;
		string colorAsStr(int);
	public:
		Pen();
		Pen(int, int, string, int, int, double);
		Pen(const Pen&);
		~Pen();
		void print();
		int getPenColor();
		int getInkColor();
		void setPenColor(int);
};