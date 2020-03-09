//Name: Autumn Henderson
//Date: November 14th, 2018
//Title: Lab 12
//Description: This program takes a picture and either does nothing to the picture,
//inverts it, flips it upside down, or flips it from left to right.

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ostream>
#include <limits>

using namespace std;

//Struct Pixel creates three integers that store the red, green, and blue channel of a pixel
struct Pixel{

	unsigned int red;
	unsigned int green;
	unsigned int blue;
};

//Class Picture creates several members for handling the picture provided
class Picture{

	private:
		vector<Pixel> pixelStructures;
		unsigned int width;
		unsigned int height;
		unsigned int maxIntensity;

	public:
		Picture();
		const Pixel& get_pixel(unsigned int row, unsigned int column) const;
		Pixel& get_pixel(unsigned int row, unsigned int column);
		void set_pixel(unsigned int row, unsigned int column, const Pixel &pixel);
		void Invert();
		void flip_x();
		void flip_y();
		bool read_input(istream &in);
		void write_output(ostream &out);
};

int main(int argc, char *argv[]) {
	
	Picture aboutPic;

	ifstream ppmFile;
	
	string cinPPM;
	istringstream cinISS;

	ofstream newPPMFile;

	string consolePPM;
	ostringstream out;

	bool readFile = false;

	string inputInfo;
	string outputInfo;
	string command;

	//Initially checks argc to make sure there are at least 3 arguments provided. Warns user and quits program if there are not.
	if (argc < 3) {
		cout << "Not enough arguments. Need the following: <program_name> <file_to_open or '-'> <file_to_close or '-'> <OPTIONAL: I, Y, X commands>.\n";
		return -1;
	}

	inputInfo = argv[1];

	//Reads from cin
	if (inputInfo == "-") {
		cout << "Type in PPM file: ";
		cin >> cinPPM;
		cinISS.str(cinPPM);
		readFile = aboutPic.read_input(cinISS);
	}
	//Reads from file
	else {
		ppmFile.open(inputInfo);
		
		if(!ppmFile.is_open()) {
			cout << "Unable to open " << inputInfo << '\n';
			return -1;
		}
		readFile = aboutPic.read_input(ppmFile);
	}

	if (readFile == false) {
		cout << "Unable to read file.\n";
		return -1;
	}

	//Performs conversions
	if (argc == 4 && readFile == true) {
		command = argv[3];

		if (command == "I" || command == "i") {
			aboutPic.Invert();
		}
		else if (command == "Y" || command == "y") {
			aboutPic.flip_y();
		}
		else if (command == "X" || command == "x") {
			aboutPic.flip_x();
		}
	}

	//Writes to cout
	outputInfo = argv[2];

	if (outputInfo == "-" && readFile == true) {
		aboutPic.write_output(out);
		consolePPM = out.str();
		cout << consolePPM;
	}
	//Writes to file
	else if (readFile == true) {
		newPPMFile.open(outputInfo);

		if(!newPPMFile.is_open()) {
			cout << "Unable to open " << outputInfo << '\n';
			return -1;
		}

		aboutPic.write_output(newPPMFile);
	}
	
	//Closes files
	ppmFile.close();
	newPPMFile.close();

	return 0;
}

//Constructor Picture sets width, height, and maximum intensity to 0
Picture::Picture() {

	width = 0;
	height = 0;
	maxIntensity = 0;
}

//Accessor get_pixel takes a row and a column and returns the given Pixel
const Pixel& Picture::get_pixel(unsigned int row, unsigned int column) const {
	return pixelStructures.at((row * width) + column);
}

//Mutator get_pixel takes a row and column and returns the given Pixel
Pixel& Picture::get_pixel(unsigned int row, unsigned int column) {
	return pixelStructures.at((row * width) + column);
}

//Mutator set_pixel takes a row and a column and a Pixel structure and sets the given
//pixel to the new Pixel value
void Picture::set_pixel(unsigned int row, unsigned int column, const Pixel &pixel) {
	get_pixel(row, column) = pixel;
}

//Mutator Invert takes no arguments and returns nothing. It will invert the picture by 
//updating the vector.
void Picture::Invert() {
	
	Pixel oldPixel;
	Pixel newPixel;
	unsigned int x;
	unsigned int y;

	for(x = 0; x < height; ++x) {
		for(y = 0; y < width; ++y) {
			oldPixel = get_pixel(x, y);
			newPixel.red = maxIntensity - oldPixel.red;
			newPixel.green = maxIntensity - oldPixel.green;
			newPixel.blue = maxIntensity - oldPixel.blue;
			set_pixel(x, y, newPixel);
		}
	}
}

//Mutator flip_x takes no arguments and returns nothing. It will flip the picture
//upside down.
void Picture::flip_x() {
	
	Pixel topPixel;
	Pixel bottomPixel;
	unsigned int x;
	unsigned int y;

	for(x = 0; x < height/2; ++x) {
		for(y = 0; y < width; ++y) {
			topPixel = get_pixel(x, y);
			bottomPixel = get_pixel((height - 1 - x), y);

			set_pixel(x, y, bottomPixel);
			set_pixel(height - 1 - x, y, topPixel);
		}
	}
}

//Mutator flip_y takes no arguments and returns nothing. It will flip the picture
//from left to right.
void Picture::flip_y() {
	
	Pixel leftPixel;
	Pixel rightPixel;
	unsigned int x;
	unsigned int y;

	for(x = 0; x < height; ++x) {
		for(y = 0; y < (width/2); ++y) {
			leftPixel = get_pixel(x, y);
			rightPixel = get_pixel(x, width - 1 - y);
			
			set_pixel(x, y, rightPixel);
			set_pixel(x, width - 1 -y, leftPixel);
		}
	}
}

//Mutator read_input takes an istream and processes the file by assigning the P3, width,
//height, maximum intensity, and all rgb pixel values.
bool Picture::read_input(istream &in) {

	bool ableToRead = false;
	istringstream ISS;

	string fileIsP3;
	string widthHeight;
	string maxI;
	string process;
	string pixels;

	unsigned int i = 0;
	unsigned int WH;

	Pixel pix;

	//Process P3 line
	getline(in, fileIsP3);
	
	if (fileIsP3 != "P3") {
		cout << "File is not P3.\n";
		return ableToRead;
	}

	//Process width and height
	do {
		getline(in, widthHeight);
		ISS.clear();
		ISS.str(widthHeight);
		
		//Ignores comments to get width and height
		if(widthHeight.at(0) == '#') {
			ISS.clear();
			ISS.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else{
			break;
		}
	}while (true);

	ISS >> width >> height;
	
	WH = width * height;

	//Reserves space using width * height
	pixelStructures.reserve(WH);

	//Process max intensity
	do {
		getline(in, maxI);
		ISS.clear();
		ISS.str(maxI);

		//Ignores comments to get maximum intensity
		if(maxI.at(0) == '#') {

			ISS.clear();
			ISS.ignore(numeric_limits<streamsize>::max(), '\n'); 
		}
		else{
			break;
		}
	}while (true);

	ISS >> maxIntensity;

	//Process pixels

	while (getline(in, process)) {
		if (process.at(0) == '#')
			continue;
		else
			pixels += process + " ";
	}
	
	ISS.clear();
	ISS.str(pixels);
	
	//Insert pixels into vector
	while ((ISS >> pix.red >> pix.green >> pix.blue) && (i <= WH)) {
		//Checks intensity
		if (pix.red > maxIntensity) {
			cout << "Red pixel being stored in vector location " << i 
				<< " is greater than the max intensity and is being changed to " 
				<< maxIntensity << '\n';
			pix.red = maxIntensity;
		}

		if (pix.green > maxIntensity) {
		cout << "Green pixel being stored in vector location " << i 
			<< " is greater than the max intensity and is being changed to " 
			<< maxIntensity << '\n';
			pix.green = maxIntensity;
		}

		if (pix.blue > maxIntensity) {
		cout << "Blue pixel being stored in vector location " << i 
			<< " is greater than the max intensity and is being changed to " 
			<< maxIntensity << '\n';
			pix.blue = maxIntensity;
		}
		
		//Places pixel in vector
		pixelStructures.push_back(pix);
		++i;
	}

	//Checks to make sure there is enough information
	if (i == (WH)) {
		ableToRead = true;
	}
	else if (i < (WH)) {
		cout << "Not enough information in file to change picture.\n";
		return ableToRead;
	}

	return ableToRead;
}

//Accessor write_output takes an ostream and returns nothing. It places the new
//picture values into the ostream.
void Picture::write_output(ostream &out) {

	Pixel newPixels;
	out.clear();

	out << "P3.\n";
	out << width << " " << height << '\n';
	out << maxIntensity << '\n';

	for (unsigned int i = 0; i < (width * height); ++i) {
		newPixels = pixelStructures.at(i);
		
		out << newPixels.red << " " << newPixels.green << " " << newPixels.blue << '\n';
	}
}
