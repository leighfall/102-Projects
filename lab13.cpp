#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdexcept>
using namespace std;

class doublevector {
     static constexpr double DOUBLE_DEFAULT_VALUE = -5.55;
     double *mValues;
     int mNumValues;
public:
     doublevector();
     ~doublevector();
     void resize(int new_size, double initial_value=DOUBLE_DEFAULT_VALUE);
     void push_back(double value);
     double &at(int index);
     const double &at(int index) const;
     unsigned long size() const;
};
void print_all(const doublevector &v)
{
     if (v.size() == 0) {
           cout << "Vector is empty.\n";
     }
     else {
          unsigned long i;
          for (i = 0;i < v.size();i++) {
                cout << "[" << setfill('0') << right << setw(3) << i
                     << "] = " << fixed << setprecision(4) << v.at(i)
                     << '\n';
          }
     }
}
int main()
{
      doublevector v;
      do {
           string command;
           cout << "Enter a command ('quit' to quit): ";
           if (!(cin >> command) || command == "quit") {
                break;
           }
           else if (command == "push_back") {
                double value;
                cin >> value;
                v.push_back(value);
		cout << "Pushed back "
		     << fixed << setprecision(4)
		     << value << '\n';
           }
           else if (command == "resize") {
                string line;
                int new_size;
                double initial;
                cin >> new_size;
                getline(cin, line);
                istringstream sin(line);

                if (sin >> initial)
                     v.resize(new_size, initial);
                else
                     v.resize(new_size);
           }
           else if (command == "size") {
                cout << v.size() << '\n';
           }
           else if (command == "print") {
                print_all(v);
           }
           else if (command == "get") {
                int index;
                cin >> index;
                try {
                     cout << "Value at " << index << " = "
		          << setprecision(4) << fixed
                          << v.at(index) << '\n';;
                }
                catch(out_of_range &err) {
                     cout << err.what() << '\n';
                }
           }
           else if (command == "set") {
		   double d;
		   int index;
                   cin >> index >> d;
                   try {
			v.at(index) = d;
                        cout << "SET: " << index << " = "
			     << setprecision(4) << fixed
                             << v.at(index) << '\n';;
                   }
                   catch(out_of_range &err) {
                        cout << err.what() << '\n';
                   }
           }
           else if (command == "clear") {
                v.resize(0);
           }
           else {
                cout << "Invalid command '" << command << "'\n";
           }
      } while(true);
      cout << endl;
      return 0;
}
//Write your class members below here.

//Name: Autumn Henderson
//Date: 11/21/2018
//Title: Lab 13
//Description: This program creates a vector class.

doublevector::doublevector() {
	mNumValues = 0;
}

doublevector::~doublevector() {
	mValues = nullptr;
}

void doublevector::resize(int new_size, double initial_value) {
	
	//Allocates mValues memory if it has not been allocated
	if (mValues == nullptr) {
		mValues = new double [new_size];
		mNumValues = new_size;
		for (int i = 0; i < mNumValues; ++i)
			mValues[i] = initial_value;
		
		if (mValues != nullptr)
			delete [] mValues;
	}

	//Grows the vector
	if (new_size > mNumValues && mValues != nullptr) {

		double *newPtr = new double [new_size];

		for (int i = 0; i < mNumValues; ++i) {
			newPtr[i] = mValues[i];
		}

		for (int i = 0; i < (new_size - mNumValues); ++i) {
			newPtr[i + mNumValues] = initial_value;
		}

		//All values for the new pointer have been assigned
		
		mValues = newPtr;
		
		mNumValues = new_size;
		
	}

	//Shrinks the vector
	else if (new_size < mNumValues && mValues != nullptr) {
		double *newPtr;
		newPtr = new double [new_size];
		for (int i = 0; i < new_size; ++i)
			newPtr[i] = mValues[i];
		
		mValues = newPtr;
		
		mNumValues = new_size;
	}

	//Deletes mValues
	if (mValues != nullptr && new_size == 0) {
		delete [] mValues;
	}
}

void doublevector::push_back(double value) {
		
		resize(mNumValues + 1, value);
}

double& doublevector::at(int index) {

	if (index >= mNumValues) {
		ostringstream sout;
		sout << "Invalid index #" << index;
		throw out_of_range(sout.str());
	}

	return mValues[index];
}

const double& doublevector::at(int index) const {

	if (index >= mNumValues) {
		ostringstream sout;
		sout << "Invalid index #" << index;
		throw out_of_range(sout.str());
	}

	return mValues[index];
}

unsigned long doublevector::size() const {
	return mNumValues;
}
