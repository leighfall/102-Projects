/*Autumn Henderson
 * Lab2
 * August 29th, 2018
 * Description: This program asks for a user's first and middle names, their age, and their address,
 * and then outputs their movie star name, who they will play, and what their new address is.
 */

#include <iostream>
#include <string>

using namespace std;

int main(){

	//Primary Variables

	string firstName, middleName, streetName, streetType;
	int age, numStreet;

	//User Input

	cout << "Enter your first and middle names: ";
	cin >> firstName >> middleName;

	cout << "Enter your age: ";
	cin >> age;

	cout << "Enter your street number, name, and type: ";
	cin >> numStreet >> streetName >> streetType;
	
	cout << "\n";

	//User's new identity

	cout << "Your movie star name is " << streetName << " " << middleName << ".\n";

	cout << "You will play a " << (numStreet % age) * 3 << " year old.\n";

	cout << "Your address is " << (age * 700) / numStreet << " " << firstName << " " << streetType << ".\n";

	return 0;
}
