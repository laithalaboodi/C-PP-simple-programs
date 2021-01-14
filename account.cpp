#include <iostream>
#include <iomanip>
#include <string>
#include "pch.h"

using namespace std;

//bankAccount.h
#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

//defining the abstract class that will be inherited to different types of bank accounts
class bankAccount
{
public:
	//defining the constructor with argument which intialises the account number , name and intial balance
	bankAccount(int acctNum, string name, double initialBalance)
	{
		m_AcctNumber = acctNum;
		m_Name = name;
		m_Balance = initialBalance;
	}
	//default destructor
	~bankAccount(void) {}

	//accessor function for member m_Name
	string get_Name()
	{
		return m_Name;
	}
	//accessor function for member Account Number
	int get_AcctNumber()
	{
		return m_AcctNumber;
	}

	//accessor function for m_Balance
	double get_Balance()
	{
		return m_Balance;
	}

	//defining the deposit function ,updating the amount in account by adding the amount being deposited
	void deposit(double amount)
	{
		m_Balance += amount;
		cout << "$" << amount << " has been deposited to your account" << endl;
	}
	//pure virtual function , will be defined in inherited classes
	virtual void withdraw(double amount) = 0;
	virtual void printStatement() = 0;

	//virtual function ,this function will also be defined in inherited classes. This function prints the summary of the account
	virtual void printSummary()
	{
		cout << setw(60) << setfill('-') << "" << setfill(' ') << endl;
		cout << endl << setw(25) << "" << "Account Summary" << endl << endl;
		cout << setw(25) << "Name: " << m_Name << endl;
		cout << setw(25) << "Account #: " << m_AcctNumber << endl;
		cout << setw(25) << "Current Balance: $" << m_Balance << endl;
	}

protected:
	//protected data member Name,Account Number, m_Balance
	string m_Name;
	int m_AcctNumber;
	double m_Balance;
};
#endif


//certificateOfDeposit.h
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
//class certificateOfDeposit is inherited from bankAccount
class certificateOfDeposit : public bankAccount
{
public:
	//constructor intializing the data members of class, the account number ,name ,intialBalance will get intialised from bankAccount class's constructor
	certificateOfDeposit(int acctNum, string name, double initialBalance, int matMon)
		: bankAccount(acctNum, name, initialBalance)
	{
		m_MaturityMonths = matMon;
		m_CurrentMonth = 1;
		m_InterestRate = 4.75;
	}
	//default destructor
	~certificateOfDeposit(void) {}
	//defining its own withdraw function ,updating the balance by subtracting the withdrawal amount
	void withdraw(double amount)
	{
		if (m_Balance - amount < 0)
		{
			cout << "Declined: Insufficient funds remain to withdraw that amount" << endl;
			return;
		}
		m_Balance -= amount;
	}

	//defining its own print summary function ,to print the summary of account
	void printSummary()
	{
		// Use the root base class to print common info
		bankAccount::printSummary();
		cout << setw(25) << "Interest rate: " << m_InterestRate << "%" << endl;
		cout << setw(25) << "Maturity Months: " << m_MaturityMonths << endl;
		cout << setw(25) << "Current Month: " << m_CurrentMonth << endl;
		cout << endl << setw(60) << setfill('-') << "" << setfill(' ') << endl;

	}
	//printStatement function same as printSummary() except the last additional line
	void printStatement()
	{
		printSummary();
		cout << "A full implementation would also print a Certificate of Deposite Account Statement here." << endl;
	}
private:
	//private data members
	double m_InterestRate;
	int m_MaturityMonths;
	int m_CurrentMonth;
};


//checkingAccount.h
#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
//class checkingAccount is inherited from bankAccount
class checkingAccount :public bankAccount
{
public:
	//constructor intializing the data members of class, the account number ,name ,intialBalance will get intialised from bankAccount class's constructor
	checkingAccount(int acctNum, string name, double initialBalance)
		: bankAccount(acctNum, name, initialBalance)
	{
	}
	//default destructor
	~checkingAccount(void) {}
	//writeCheck function will be defined in the classes which will be inherited from checkingAccount class
	virtual void writeCheck(double amount) = 0;
	//defining its own withdraw function ,updating the balance by subtracting the withdrawal amount
	void withdraw(double amount)
	{
		if (m_Balance - amount < 0)
		{
			cout << "Declined: Insufficient funds remain to withdraw that amount" << endl;
			return;
		}
		if (m_Balance - amount < mMinimumBalance)
		{
			cout << "Declined: Minimum balance requirement prohibits this withdrawal" << endl;
			return;
		}
		m_Balance -= amount;
	}
	//defining its own printStatement function ,to print the statement of account
	void printStatement()
	{
		printSummary();
		cout << endl << "A full implementation would also print details of a Checking Account Statement here." << endl << endl;
	}
protected:
	//protected data member m_InterestRate,m_ChecksRemaining,m_MinimumBalance
	double mInterestRate;
	int mChecksRemaining;
	double mMinimumBalance;
};
#endif






//noServiceChargeChecking.h
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

//noServiceChargeChecking is inherited from checkingAccount
class noServiceChargeChecking :public checkingAccount
{
public:
	//constructor intialises the int acctNum, string name, double initialBalance with the help of checkingAccount constructor
	noServiceChargeChecking(int acctNum, string name, double initialBalance)
		: checkingAccount(acctNum, name, initialBalance)
	{
		mInterestRate = 2.5; // Some interest rate
		mChecksRemaining = -1; // -1 no limit
		mMinimumBalance = 500; // Minimum balance
	}
	//default destructor
	~noServiceChargeChecking(void) {}
	//updating the balance by subtracting the ammount of written check
	void writeCheck(double amount)
	{
		if (m_Balance - amount < 0)
		{
			cout << "Declined: Insufficient funds remain to withdraw that amount" << endl;
			return;
		}
		m_Balance -= amount; // Assume check is cashed immediately...
	}
	//printing the summary of account
	void printSummary()
	{
		// Use the root base class to print common info
		bankAccount::printSummary();
		cout << setw(25) << "Interest rate: " << mInterestRate << "%" << endl;
		cout << setw(25) << "Minimum Balance: $" << mMinimumBalance << endl;
		cout << setw(25) << "Unlimited checks " << endl;
		cout << setw(25) << "No monthly service fee " << endl;
		cout << setw(60) << setfill('-') << "" << setfill(' ') << endl;
	}
};
//highInterestChecking.h
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

//highInterestChecking is inherited from noServiceChargeChecking class
class highInterestChecking : public noServiceChargeChecking
{
public:
	//constructor intialises the acctNum ,name ,initialBalance from the constructor of noServiceChargeChecking class constructor
	//members like m_InterestRate,m_ChecksRemaining,m_MinimumBalance will get intialised with constant values
	highInterestChecking(int acctNum, string name, double initialBalance)
		: noServiceChargeChecking(acctNum, name, initialBalance)
	{
		// The only difference between the base class noServiceChargeChecking
		// is the values of interest and minimum balance.
		// So no additional functionality needed for this one.
		mInterestRate = 5.0; // Higher interest rate
		mChecksRemaining = -1; // -1 indicates no limit
		mMinimumBalance = 1000; // Minimum balance
	}
	//default destructor
	~highInterestChecking(void) {}
};


//savingsAccount.h
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
//savingsAccount is inherited from bankAccount
class savingsAccount :public bankAccount
{
public:
	//constructor intializing the data members of class, the account number ,name ,intialBalance will get intialised from bankAccount class's constructor
	//m_InterestRate is intialised with constant value
	savingsAccount(int acctNum, string name, double initialBalance)
		: bankAccount(acctNum, name, initialBalance)
	{
		m_InterestRate = 3.99;
	}
	//destructor
	~savingsAccount(void)
	{
	}

	//defining its own withdraw function ,updating the balance by subtracting the withdrawal amount
	void withdraw(double amount)
	{
		if (m_Balance - amount < 0)
		{
			cout << "Declined: Insufficient funds remain to withdraw that amount" << endl;
			return;
		}
		m_Balance -= amount;
	}
	//defining its own print summary function ,to print the summary of account
	void printSummary()
	{
		// Use the root base class to print common info
		bankAccount::printSummary();
		cout << setw(25) << "Interest rate: " << m_InterestRate << "%" << endl << endl;
		cout << setw(60) << setfill('-') << "" << setfill(' ') << endl;
	}
	//printStatement function same as printSummary() except the last additional line
	void printStatement()
	{
		printSummary();
		cout << "A full implementation would also print a Savings Account Statement here." << endl;
	}

protected:
	//protected data member m_InterestRate
	double m_InterestRate;
};
//highInterestSavings.h
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
//highInterestSavings is inherited from savingsAccount
class highInterestSavings :public savingsAccount
{
public:
	//constructor intialises the member account number ,name,initialBalance with the help of savingsAccount's constructor
	//intialises m_MinimumBalance with the constant
	highInterestSavings(int acctNum, string name, double initialBalance)
		: savingsAccount(acctNum, name, initialBalance)
	{
		m_MinimumBalance = 5000;
	}
	//default destructor
	~highInterestSavings(void) {}
	//defining its own withdraw function ,updating the balance by subtracting the withdrawal amount
	void withdraw(double amount)
	{
		if (m_Balance - amount < 0)
		{
			cout << "Declined: Insufficient funds remain to withdraw that amount" << endl;
			return;
		}
		if (m_Balance - amount < m_MinimumBalance)
		{
			cout << "Declined: Minimum balance requirement prohibits this withdrawal" << endl;
			return;
		}
		m_Balance -= amount;
	}
	//defining its own print summary function ,to print the summary of account along with Interest rate, Minimum Balance
	void printSummary()
	{
		// Use the root base class to print common info
		bankAccount::printSummary();
		cout << setw(25) << "Interest rate: " << m_InterestRate << "%" << endl;
		cout << setw(25) << "Minimum Balance: $" << m_MinimumBalance << endl << endl;
		cout << setw(60) << setfill('-') << "" << setfill(' ') << endl;
	}

protected:
	//protected data member
	double m_MinimumBalance;
};


//serviceChargeChecking.h
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
const int MAX_CHECKS = 5;
const double SVC_CHARGE = 10.0l;
//serviceChargeChecking is inherited from checkingAccount
class serviceChargeChecking :public checkingAccount
{
public:
	//constructor intialises the acctNum, name,initialBalance with the help of constructor of checkingAccount
	//other data members like m_InterestRate, m_ChecksRemaining,m_MinimumBalance is intialised by a constant value
	serviceChargeChecking(int acctNum, string name, double initialBalance)
		: checkingAccount(acctNum, name, initialBalance)
	{
		mInterestRate = 0; // No interest
		mChecksRemaining = MAX_CHECKS; // Limit of 5 checks
		mMinimumBalance = 0; // No minimum balance
	}
	//destructor
	~serviceChargeChecking(void) {}

	//updating the balance by subtracting the ammount of written check
	void writeCheck(double amount)
	{
		if (mChecksRemaining == 0)
		{
			cout << "Declined: No more checks remaining this month" << endl;
			return;
		}

		if (m_Balance - amount < 0)
		{
			cout << "Declined: Insufficient funds remain to withdraw that amount" << endl;
			return;
		}
		mChecksRemaining--;
		m_Balance -= amount; // Assume check is cashed immediately...

	}
	//defining its own print summary function ,to print the summary of account
	void printSummary()
	{
		// Use the root base class to print common info
		bankAccount::printSummary();
		cout << setw(25) << "Checks remaining: " << mChecksRemaining << endl;
		cout << setw(25) << "Monthly service fee: $" << SVC_CHARGE << endl;
		cout << setw(25) << "No interest " << endl;
		cout << setw(25) << "No Minimum Balance " << endl;
		cout << setw(60) << setfill('-') << "" << setfill(' ') << endl;
	}
};

using namespace std;


void TestCheckingWithService()
{
	//acct object of serviceChargeChecking, values of data member is passed as argument of constructor
	serviceChargeChecking account(321, "Laith ", 1253);
	char input = 0;
	double amount;

	cout << "\t\tTesting Checking with Service Charge" << endl << endl;
	cout << "Current account overview:" << endl;
	//printing the account summary
	account.printSummary();
	cout << endl;
	while (input != 'x')
	{
		cout << "Select a transaction:" << endl;
		cout << "1 - Make a Withdrawal" << endl;
		cout << "2 - Make a Deposit" << endl;
		cout << "3 - Print Summary" << endl;
		cout << "4 - Print Monthly Statement" << endl;
		cout << "5 - Write a check" << endl;
		cout << "x - Exit Test Suite" << endl;
		cout << "Enter choice: ";
		//entering the choice
		cin >> input;
		switch (input)
		{
		case '1':
			cout << "Enter amount: ";
			cin >> amount;
			account.withdraw(amount);
			break;
		case '2':
			cout << "Enter amount: ";
			cin >> amount;
			account.deposit(amount);
			break;
		case '3':
			account.printSummary();
			break;
		case '4':
			account.printStatement();
			break;
		case '5':
			cout << "Enter amount: ";
			cin >> amount;
			account.writeCheck(amount);
			break;
		case '6':
			break;
		case 'x':
			break;
		default:
			cout << "Invalid choice" << endl;
			break;
		}
		//after choosing valid choice again printing the account summary
		account.printSummary();
		cout << endl;
	}
}
//same as above
void TestCheckingNoService()
{

	//acct is object of noServiceChargeChecking,values of data member is passed as argument of constructor
	noServiceChargeChecking acct(321, "Laith ", 1253);
	char input = 0;
	double amount;
	cout << "\t\tTesting Checking without Service Charge" << endl << endl;
	cout << "Current account overview:" << endl;
	acct.printSummary();
	cout << endl;
	while (input != 'x')
	{
		cout << "Select a transaction:" << endl;
		cout << "1 - Make a Withdrawal" << endl;
		cout << "2 - Make a Deposit" << endl;
		cout << "3 - Print Summary" << endl;
		cout << "4 - Print Monthly Statement" << endl;
		cout << "5 - Write a check" << endl;
		cout << "x - Exit Test Suite" << endl;
		cout << "Enter choice: ";
		cin >> input;
		switch (input)
		{
		case '1':
			cout << "Enter amount: ";
			cin >> amount;
			acct.withdraw(amount);
			break;
		case '2':
			cout << "Enter amount: ";
			cin >> amount;
			acct.deposit(amount);
			break;
		case '3':
			acct.printSummary();
			break;
		case '4':
			acct.printStatement();
			break;
		case '5':
			cout << "Enter amount: ";
			cin >> amount;
			acct.writeCheck(amount);
			break;
		case '6':
			break;
		case 'x':
			break;
		default:
			cout << "Invalid choice" << endl;
			break;
		}
		acct.printSummary();
		cout << endl;
	}
}
//same as above
void TestCheckingHighInterest()
{
	//acct is object of highInterestChecking,values of data member is passed as argument of constructor
	highInterestChecking acct(321, "Laith ", 1253);
	char input = 0;
	double amount;
	cout << "\t\tTesting Checking with High Interest" << endl << endl;
	cout << "Current account overview:" << endl;
	acct.printSummary();
	cout << endl;
	while (input != 'x')
	{
		cout << "Select a transaction:" << endl;
		cout << "1 - Make a Withdrawal" << endl;
		cout << "2 - Make a Deposit" << endl;
		cout << "3 - Print Summary" << endl;
		cout << "4 - Print Monthly Statement" << endl;
		cout << "5 - Write a check" << endl;
		cout << "x - Exit Test Suite" << endl;
		cout << "Enter choice: ";
		cin >> input;
		switch (input)
		{
		case '1':
			cout << "Enter amount: ";
			cin >> amount;
			acct.withdraw(amount);
			break;
		case '2':
			cout << "Enter amount: ";
			cin >> amount;
			acct.deposit(amount);
			break;
		case '3':
			acct.printSummary();
			break;
		case '4':
			acct.printStatement();
			break;
		case '5':
			cout << "Enter amount: ";
			cin >> amount;
			acct.writeCheck(amount);
			break;
		case '6':
			break;
		case 'x':
			break;
		default:
			cout << "Invalid choice" << endl;
			break;
		}
		acct.printSummary();
		cout << endl;
	}
}
//same as above
void TestSavings()
{
	//acct is object of savingsAccount,values of data member is passed as argument of constructor
	savingsAccount acct(321, "Laith ", 1253);
	char input = 0;
	double amount;
	cout << "\t\tTesting Regular Savings" << endl << endl;
	cout << "Current account overview:" << endl;
	acct.printSummary();
	cout << endl;
	while (input != 'x')
	{
		cout << "Select a transaction:" << endl;
		cout << "1 - Make a Withdrawal" << endl;
		cout << "2 - Make a Deposit" << endl;
		cout << "3 - Print Summary" << endl;
		cout << "4 - Print Monthly Statement" << endl;
		cout << "x - Exit Test Suite" << endl;
		cout << "Enter choice: ";
		cin >> input;
		switch (input)
		{
		case '1':
			cout << "Enter amount: ";
			cin >> amount;
			acct.withdraw(amount);
			break;
		case '2':
			cout << "Enter amount: ";
			cin >> amount;
			acct.deposit(amount);
			break;
		case '3':
			acct.printSummary();
			break;
		case '4':
			acct.printStatement();
			break;
		case 'x':
			break;
		default:
			cout << "Invalid choice" << endl;
			break;
		}
		acct.printSummary();
		cout << endl;
	}
}
//same as above
void TestSavingsHighInterest()
{
	//acct is object of highInterestSavings,values of data member is passed as argument of constructor
	highInterestSavings acct(321, "Laith ", 1253);
	char input = 0;
	double amount;
	cout << "\t\tTesting High Interest Savings" << endl << endl;
	cout << "Current account overview:" << endl;
	acct.printSummary();
	cout << endl;
	while (input != 'x')
	{
		cout << "Select a transaction:" << endl;
		cout << "1 - Make a Withdrawal" << endl;
		cout << "2 - Make a Deposit" << endl;
		cout << "3 - Print Summary" << endl;
		cout << "4 - Print Monthly Statement" << endl;
		cout << "x - Exit Test Suite" << endl;
		cout << "Enter choice: ";
		cin >> input;
		switch (input)
		{
		case '1':
			cout << "Enter amount: ";
			cin >> amount;
			acct.withdraw(amount);
			break;
		case '2':
			cout << "Enter amount: ";
			cin >> amount;
			acct.deposit(amount);
			break;
		case '3':
			acct.printSummary();
			break;
		case '4':
			acct.printStatement();
			break;
		case 'x':
			break;
		default:
			cout << "Invalid choice" << endl;
			break;
		}
		acct.printSummary();
		cout << endl;
	}
}
//same as above
void TestCertificateOfDeposit()
{
	//acct is object of certificateOfDeposit,values of data member is passed as argument of constructor
	certificateOfDeposit account(321, "Laith ", 1253, 6);
	char input = 0;
	double amount;
	cout << "\t\tTesting High Interest Savings" << endl << endl;
	cout << "Current account overview:" << endl;
	account.printSummary();
	cout << endl;
	while (input != 'x')
	{
		cout << "Select a transaction:" << endl;
		cout << "1 - Make a Withdrawal" << endl;
		cout << "2 - Make a Deposit" << endl;
		cout << "3 - Print Summary" << endl;
		cout << "4 - Print Monthly Statement" << endl;
		cout << "x - Exit Test Suite" << endl;
		cout << "Enter choice: ";
		cin >> input;
		switch (input)
		{
		case '1':
			cout << "Enter amount: ";
			cin >> amount;
			account.withdraw(amount);
			break;
		case '2':
			cout << "Enter amount: ";
			cin >> amount;
			account.deposit(amount);
			break;
		case '3':
			account.printSummary();
			break;
		case '4':
			account.printStatement();
			break;
		case 'x':
			break;
		default:
			cout << "Invalid choice" << endl;
			break;
		}
		account.printSummary();
		cout << endl;
	}
}
int main()
{
	char input;
	cout << "What type of account do you want to open?" << endl;
	cout << "1 - Checking with Service Charge" << endl;
	cout << "2 - Checking without Service Charge" << endl;
	cout << "3 - Checking with High Interest" << endl;
	cout << "4 - Savings" << endl;
	cout << "5 - Savings with High Interest" << endl;
	cout << "6 - Certificate of Deposit" << endl;
	cout << "Enter choice: ";
	//entering the choice
	cin >> input;
	switch (input)
	{
	case '1':
		//Checking with Service Charge
		TestCheckingWithService();
		break;
	case '2':
		//Checking without Service Charge
		TestCheckingNoService();
		break;
	case '3':
		//Checking with High Interest
		TestCheckingHighInterest();
		break;
	case '4':
		//for Savings account
		TestSavings();
		break;
	case '5':
		//Savings with High Interest
		TestSavingsHighInterest();
		break;
	case '6':
		//for Certificate of Deposit
		TestCertificateOfDeposit();
		break;
	default:
		cout << "Invalid choice" << endl;
		break;
	}
}
