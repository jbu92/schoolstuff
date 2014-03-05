#include "Pen.h"
#include <string>
using namespace std;
class MemPen : public Pen{
	private:
		int memory;
	public:
		MemPen();
		MemPen(int, int, int, string, int, int, double);
		MemPen(const MemPen&);
		~MemPen();
		void print();
		int getMem();
		void setMem(int);
};