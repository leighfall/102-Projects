//Name: Autumn Henderson
//Date: October 10th, 2018
//Title: Lab 6
//Description: This program takes a file containing information about a ticket within
//a time frame and calculates a fine and outputs ticket information and the fine to a new file.

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <ostream>

using namespace std;

int main() {

	//Variables for:
	
	//Read and open input file
	ifstream ticketFile;
	string ticketFileName;

	//Read and open output file
	ofstream outputFile;
	string outputFileName;

	//Read in ticket line and process
	string ticketLine;
	istringstream tlSS;

	//Report start and end dates
	int rsmonth, rsday, rsyear;
	int remonth, reday, reyear;

	//Input file data
	string citationNum;
	int month, day, year, clockedSpeed, speedLimit;
	char roadType;

	//Fine calculators
	double fine = 0;
	int difference = 0;
	const double INTERSTATE = 5.2252;
	const double HIGHWAY = 9.4412;
	const double RESIDENTIAL = 17.1525;
	const double OTHER_ROAD_TYPE = 12.152;

	//Month conversion
	const string MONTHS[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct",
		"Nov", "Dec"};
	string threeLetterMonth;

	//For the for loops
	int i;

	//To convert dates
	double monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	double reportStartValue = 0;
	double reportEndValue = 0;
	double inputReportValue;


	//Handles ticket file
	cout << "Enter a ticket file: ";
	cin >> ticketFileName;

	ticketFile.open(ticketFileName);

	if (!ticketFile.is_open()) {
		cout << "Unable to open " << ticketFileName << "\n";
	}
	//Handles output file if ticket file was able to open
	else {
		cout << "Enter a report file: ";
		cin >> outputFileName;

		outputFile.open(outputFileName);

		if (!outputFile.is_open()){
			cout << "Unable to open " << outputFileName << "\n";
		}
		//Ticket and output files were both able to open
		else {
			cout << "Enter report start date (mm dd yyyy): ";
			cin >> rsmonth >> rsday >> rsyear;

			cout << "Enter report end date   (mm dd yyyy): ";
			cin >> remonth >> reday >> reyear;

			//Convert report start date and report end date into comparable values
			for (i = 0; i < rsmonth - 1; ++i) {
				reportStartValue += monthDays[i];
			}
			reportStartValue += rsday;
			reportStartValue = (reportStartValue/365.0) + rsyear;
				
			for (i = 0; i < remonth - 1; ++i) {
				reportEndValue += monthDays[i];
			}
			reportEndValue += reday;
			reportEndValue = (reportEndValue/365.0) + reyear;
							
			//Start reading in lines from ticket file
			while (getline(ticketFile, ticketLine)) {
				
				tlSS.clear();
				tlSS.str(ticketLine);

				//Process line into variables
				tlSS >> citationNum >> month >> day >> year >> clockedSpeed
					>> speedLimit >> roadType;

				//Converts year to yyyy
				if (year < 100) {
					year += 2000;
				}
				
				inputReportValue = 0;

				//Converts Date in Report to comparable values
				for (i = 0; i < month - 1; ++i) {
					inputReportValue += monthDays[i];
				}
				inputReportValue += day;
				inputReportValue = (inputReportValue/365.0) + year;
					
				//Checks to see if input report value is within the other values and makes conversions
				if (inputReportValue >= reportStartValue && inputReportValue <= reportEndValue) {
					//Input day
					outputFile << setw(2) << setfill('0') << day;

					//Change month
					for (i = 0; i < 12; ++i) {
						if ((i + 1) == month) {
							threeLetterMonth = MONTHS[i];
						}
					}

					//Input month, year & citation
					outputFile << "-" << threeLetterMonth << "-" << year << " " 
						<< left << setw(10) << setfill(' ') << citationNum;

					//Calculate fine and input
					difference = clockedSpeed - speedLimit;

					switch (roadType) {
						case 'i':
						case 'I':
							fine = difference * INTERSTATE;
							break;
						case 'h':
						case 'H':
							fine = difference * HIGHWAY;
							break;
						case 'r':
						case 'R':
							fine = difference * RESIDENTIAL;
							break;
						default:
							fine = difference * OTHER_ROAD_TYPE;
							break;
					}

					if (fine < 0) {
						fine = 0;
					}

					outputFile << "$" << right << setw(9) << fixed << setprecision(2) << fine << '\n';
				}
			}
		}
	}
	
	ticketFile.close();
	outputFile.close();
	return 0;
}
