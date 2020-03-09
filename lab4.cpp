//Author: Autumn Henderson
//Title: Lab 4
//Date: September 18th, 2018
//Description: This program will take in vehicle input and mpg and
//output average mpg for the vehicle.

#include <iostream>
#include <limits>

using namespace std;

int main() {

	//Command variables
	string car = "car";
	string truck = "truck";
	string done = "done";
	string command;

	//True or False variables
	bool isThereCars = false;
	bool isThereTrucks = false;

	//Miles & Gallons for Car variables
	double carMiles = 0;
	double carGallons = 0;
	double totalCarMiles = 0;
	double totalCarGallons = 0;

	//Miles & Gallons for Truck variables
	double truckMiles = 0;
	double truckGallons = 0;
	double totalTruckMiles = 0;
	double totalTruckGallons = 0;

	//Average MPG variables
	double avgCarMPG = 0;
	double avgTruckMPG = 0;

	do {  //do-while loop checks for command.
		cout << "Enter command: ";
		cin >> command;

		//If statement checks for the command to ask for miles and gallons.

		while (!((command == car) || (command == truck) || (command == done))) {
			cout << "Unknown command.\n";
			cout << "Enter command: ";
			cin >> command;
		}

		//If the command is "car":
		if (command == car) { 
			isThereCars = true;
		
			//Check car miles
			do {
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}

				cout << "Enter car's miles: ";

			}while (!(cin >> carMiles));
			
			totalCarMiles += carMiles;
			
			//Check car gallons
			do {
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}

				cout << "Enter car's gallons: ";

			}while (!(cin >> carGallons));

			totalCarGallons += carGallons;			
		}

		//If the command is "truck":
		else if (command == truck) {
			isThereTrucks = true;
			
			//Check truck miles
			do {
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				
				cout << "Enter truck's miles: ";

			}while (!(cin >> truckMiles));

			totalTruckMiles += truckMiles;

			//Check truck gallons
			do {
				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}

				cout << "Enter truck's gallons: ";

			}while (!(cin >> truckGallons));

			totalTruckGallons += truckGallons;
		}

		//Else the command was "done"
		else {
			break;
		}
		
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

	}while (!(command == done));

	//If there were cars, will calculate average MPG. Otherwise, no cars.
	if (isThereCars == true) {
		avgCarMPG = totalCarMiles / totalCarGallons;
		cout << "Average car MPG = " << avgCarMPG << "\n";
	}
	else {
		cout << "Fleet has no cars.\n";
	}

	//If there were trucks, will calculate average MPG. Otherwise, no trucks.
	if (isThereTrucks == true) {
		avgTruckMPG = totalTruckMiles / totalTruckGallons;
		cout << "Average truck MPG = " << avgTruckMPG << "\n";
	}
	else {
		cout << "Fleet has no trucks.\n";
	}

	return 0;
}
