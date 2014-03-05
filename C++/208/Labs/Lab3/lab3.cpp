//Course: 4002-208
//Author: 
//Assignment:
//Purpose:.
//Caveats:

//include library for input and output
#include <iostream>
#import <string>
#import <iomanip>
using namespace std;
string company, stock;
double sold, price, spent, profit, made, commissionBuy, comissionSell, total, made1;
int number;
const double COMMISSION_BUY = .0125;
const double COMMISSION_SELL = .011;
int main ( )
{
	//Housekeeping
    cout << fixed << showpoint;
	cout << setprecision(2);
	
	//Input and validation thereof
	cout << "Input name of company: ";
	getline (cin, company);
	cout << "Enter stock symbol: ";
	getline (cin, stock);
	cout << "Purchase price per share in USD: ";
	cin >> price;
	if(price <= 0)
	{
		cout << "Price must be > 0. Try again." << endl;
		system("pause");
		return 0;
	}
	cout << "Sell price per share in USD: ";
	cin >> sold;
	cout << "Number of shares purchased: ";
	cin >> number;
	cout << endl;
	if(number < 10 || number > 1000)
	{
		cout << "Number of shares must be between 10 and 1000." << endl;
		system("pause");
		return 0;
	}
	if(number % 10 != 0)
	{
		cout << "Number of shares must be a multiple of 10 for some reason." << endl;
		system("pause");
		return 0;
	}
	
	//Math
	commissionBuy = price * double(number) * COMMISSION_BUY;
	comissionSell = sold * double(number) * COMMISSION_SELL;
	spent = (price * double(number));
	made = (sold * double(number));
	total = spent + commissionBuy;
	made1 = made - comissionSell;
	profit = made1 - total;

	//Output
	cout << company << " (" << stock << ")" << endl;
	cout << setw(10) << spent << endl;
	cout << setw(10) << commissionBuy << endl;
	cout << setw(10) << total;
	cout << endl << endl;
	cout << setw(10) << made << endl;
	cout << setw(10) << comissionSell << endl;
	cout << setw(10) << made1 << endl << endl;
	cout << "Profit : " << profit;
	//Freeze DOS window until user presses a key.
	cout << endl;
	system("pause");
	//terminate program
	return 0;
} //end of main function
    
