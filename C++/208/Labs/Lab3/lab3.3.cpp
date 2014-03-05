//Course: 4002-208
//Author: Rayno Niemi
//Lab 3
//Program: lab3ex1.cpp
//Purpose: Read in the data for a stock including name, symbol, cost per share
//         and number of  shares.   
//         Compute the purchase price for the stock based on a 1.25% commission

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main ( )
{  
    //constant section
    const double COMMISSION_RATE_BUY  = 0.0125;  //commisison rate of 1.25% to buy shares
    const double COMMISSION_RATE_SELL = 0.0110;  //commisison rate of 1.1% to sell shares
      
    //variable declarations
    double priceBuy   = 0.0;   //price per share at time of purchase
    int    numShares  = 0;     //number of shares purchased
    double costShares = 0.0;   //cost of shares with no commission
    double commission = 0.0;   //commission for shares
    double totalCost  = 0.0;   //cost of shares including fees
    string company    = "";    //name of company
    string symbol     = "";    //symbol of company
    char bs;
while(1)
{
	//input and validation
    cout << "Enter name of company: ";
    getline(cin, company);
    cout << "Enter symbol: ";
    cin >> symbol;
    cout << "Enter price per share: ";
    cin >> priceBuy;
	if(priceBuy <= 0)
	{
		cout << "Price must be > 0. Try again." << endl;
		system("pause");
		return 0;
	}
    cout << "Enter number of shares purchased: ";
    cin >> numShares;
	if(numShares < 10 || numShares > 1000)
	{
		cout << "Number of shares must be between 10 and 1000." << endl;
		system("pause");
		return 0;
	}
	if(numShares % 10 != 0)
	{
		cout << "Number of shares must be a multiple of 10 for some reason." << endl;
		system("pause");
		return 0;
	}
	cout << "B for buying S for selling: ";
	cin >> bs;
	if(bs != 'b' && bs != 'B' && bs != 's' && bs != 'S')
	{
		cout << "Try again dude... wow you fail" << endl;
		system("pause");
		return 0;
	}
    
    //math and output
	switch(bs)
	{
		case 'B':		
		case 'b':
		{
			costShares = priceBuy * static_cast <double> (numShares);
			commission = costShares * COMMISSION_RATE_BUY;		
			if(commission > 100)
				commission = 100;
			totalCost   = costShares + commission;
			cout << endl;
			cout << showpoint << fixed << setprecision(2);
			cout << company << " (" << symbol << ")"   << endl;

			cout << setw(17) << "Cost of Purchase:" << setw(10) << costShares << endl;
			cout << setw(17) << "Commission:"       << setw(10) << commission << endl;
			cout << setw(17) << "Total cost:"       << setw(10) << totalCost  << endl;
			break;
		}
		case 'S':
		case 's':
		{
			costShares = priceBuy * static_cast <double> (numShares);
			commission = costShares * COMMISSION_RATE_SELL;
			if(commission > 100)
				commission = 100;
			totalCost   = costShares - commission;
			cout << endl;
			cout << showpoint << fixed << setprecision(2);
			cout << company << " (" << symbol << ")"   << endl;

			cout << setw(17) << "Cost of Sale:" << setw(10) << costShares << endl;
			cout << setw(17) << "Commission:"       << setw(10) << commission << endl;
			cout << setw(17) << "Total profit:"       << setw(10) << totalCost  << endl;
			break;
		}
	}
cin.ignore();
}
    //Freeze DOS window until user presses a key
    cout << endl;
    system("pause");
    //terminate program
    return 0;
} //end of main function
    
