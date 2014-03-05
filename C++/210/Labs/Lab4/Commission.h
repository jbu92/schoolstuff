#include <iostream>
using namespace std;
class Commission{
	private:
		int idNum;
		double base,sales,rate;
	public:
		Commission();
		Commission(int, double, double, double);
		~Commission();
		void copy(Commission);
		bool setIdNum(int);
		bool setBase(double);
		bool setSales(double);
		bool setRate(double);
		int getIdNum();
		double getBase();
		double getSales();
		double getRate();
		double calcSalary();
		void operator= (const Commission& input);
		bool operator== (const Commission& commission2);
		friend bool equal(Commission& comm1, Commission& comm2);
};

