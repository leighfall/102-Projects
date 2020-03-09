/*Author: Autumn Henderson
  Date: September 11th, 2018
  Description: This program allows the user to enter operands and an operator and will perform
  the operation.
*/

#include <iostream>
#include <string>

using namespace std;

int main () {

	//Declared Variables
	double leftOperand, rightOperand, result;
	char operation;
	bool noAbsResult = false;
	bool noResult = false;
	string otherOperations = "Aa+Ss-Mm*Dd/";
	bool invldOperand = false;

	cout << "Enter left operand: ";
	
	if (cin >> leftOperand) {             //Validates left operand
		cout << "Enter operation: ";
		cin >> operation;

		switch (operation) {		//Checks for absolute value operand
			case 'B':
			case 'b':
			case '|':
				if (leftOperand < 0) {		//Performs absolute value without calling function
					result = leftOperand * (-1);
				}
				else {
					result = leftOperand;
				}
				break;

			default:
				noAbsResult = true; //Tells us absolute value is not being performed.
			break;
				
		}

		//Checks if absolute value was not performed and the operator does not match the rest
		if ((otherOperations.find(operation) == string::npos) && (noAbsResult == true)) {
			cout << "Unknown operation.\n";
			invldOperand = true;
		}

		//Will enter if result was not assigned because it was not absolute value.
		//Asks for right operand and performs the rest of the operations.
		if ((noAbsResult == true) && (invldOperand != true)) {

			cout << "Enter right operand: ";
			
			if (cin >> rightOperand) { //Checks for operations
				switch (operation) {
					case 'A':
					case 'a':
					case '+':
						result = leftOperand + rightOperand;
						break;
					case 'S':
					case 's':
					case '-':
						result = leftOperand - rightOperand;
						break;
					case 'M':
					case 'm':
					case '*':
						result = leftOperand * rightOperand;
						break;
					case 'D':
					case 'd':
					case '/':
						result = leftOperand / rightOperand;
						break;
					default:
						noResult = true;
						break;
				}	
			}
			else {		//Hits this statement if right operand was not correct
				cout << "Invalid right operand.\n";
				noResult = true;
			}
		}
	}

	else {	//Hits this statement if left operand was not correct
		cout << "Invalid left operand.\n";
		noResult = true;
	}
	
	//Prints out result if a result was obtained and noResult was never assigned "true"
	if ((noResult != true && invldOperand !=true)) {
		cout << "Result = " << result << "\n";
	}

	return 0;
}
