#include <string>
using namespace std;
class Supply{
	private:
		string desc;
		int stockNo;
		int quant;
		double price;
	public:
		Supply();
		Supply(string, int, int, double);
		Supply(const Supply&);
		~Supply();
		virtual void print();
		double getPrice();
		void setPrice(double);
};
