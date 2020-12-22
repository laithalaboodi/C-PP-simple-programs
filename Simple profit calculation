/*
Laith Alaboodi
Simple profit calculation 
*/

#include "pch.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::string;


//welcome message
void welcomeMessage() {
	cout << "V0.1"<<endl;
	cout << "-----------------------------------------------------------------------------------------" << endl;
	cout << "* Welcome to Laith Alaboodi Program *" << endl;
	cout << "* This program is to calculate the profit of your milk production *" << endl; 
	cout << "-----------------------------------------------------------------------------------------" << endl;
}

//method to get total amount of milk produced in the morning 
double getMilkProduced() {
	double milkProduced;
	cout << "How much milk did you produce? "<<endl;
	cin >> milkProduced;
	return milkProduced;
}

//this method is where the calc will be 
void calcMethod(double milkProduced) {
	double cartonsRequired; 
	//making the constant 
	const double CARTON_SIZE = 3.78;
	const double PRODUCTION_COST = 0.38;
	const double CARTON_PROFIT = 0.27;

	cartonsRequired = milkProduced / CARTON_SIZE;

	cout << "That is going to require " << static_cast<int>(cartonsRequired) << " cartons" << endl;
	cout << "Total Cost to Produce: $" << cartonsRequired * PRODUCTION_COST << endl;
	cout << "Total Profit: $" << cartonsRequired * CARTON_PROFIT << endl;
}
//ending message
void endingMessage() {
	cout << "-----------------------------------------------------------------------------------------" << endl;
	cout << "* Thank you for using this program! *" << endl;
	cout << "*HAVE A WONDERFUL DAY*" << endl;
	cout << "-----------------------------------------------------------------------------------------" << endl;
}

int main()
{
	welcomeMessage();
	char choice;
	while (true)
	{
		double milkProduced = getMilkProduced();
		calcMethod(milkProduced);
		cout << "-----------------------------------------------------------------------------------------" << endl;
		cout << "Would you like to perform other calculation?(Y/N)" << endl;
		cin >> choice;
		if (choice == 'N' || choice == 'n') {
		break;
		}
	}
	endingMessage();
	system("pause");
	return 0;
}
