
#include <iostream>
#include <fstream>
#include <vector>

#include "morse.hpp"
/**
 * gets valid directory from user input
 */
std::string getDir() {
	// stores the last directory used
	static std::string cache;
	// directory
	std::string dir;
	bool validIn = false;
	do {
		std::cout << "Enter file directory: ";
		// input
		std::getline(std::cin, dir);
		// if user uses last directory
		if (dir.compare("last") == 0) {
			// sets the directory to what was in the cache
			dir = cache;
			break;
		}
		std::fstream file;
		// opens file, might succeed
		file.open(dir);
		// if it's opened, terminate loop
		validIn = file.is_open();

	} while (!validIn);
	cache = dir;
	std::cout << "Thank you for the directory! \n";
	return dir;
}
/**
 * gets text to convert
 */
std::string getText() {
	std::string txt;
	std::cout << "Enter text to convert: ";
	// puts input into txt
	std::getline(std::cin, txt);
	return txt;
	std::cout << "Thank you for the text! \n";
}
/**
 * represents various operation code
 */
enum opcode {
	STOP, READ, WRITE, READBIN, BAD = -1
};
/**
 * gets the proper operation from the user
 */
opcode getOp() {
	// 0 for non init 1 for read 2 for write
	opcode op = BAD;
	// whether or not input is valid
	bool validIn;
	// user input
	std::string input;
	do {
		std::cout << "What would you like to do? 'r' for read, 'w' for write, 'b' for read binary and 's' for stop: ";
		// user input
		std::getline(std::cin, input);
		// will be set to false if input is invalid
		validIn = true;
		// if the string is "w"
		if (input.compare("w") == 0) {
			// operation is write
			op = WRITE;
		// if the string is "r"
		} else if (input.compare("r") == 0) {
			// operation is read
			op = READ;
		// if the string is "s"
		} else if (input.compare("s") == 0) {
			// operation is stop
			op = STOP;
		} else if (input.compare("b") == 0) {
			op = READBIN;
		} else {
			validIn = false;
		}

	} while (!validIn);
	std::cout << "Thank you for the operation! \n";
	return op;
}
/**
 * writes some text to a file
 */
void write() {
	const std::string dir = getDir();
	const std::string txt = getText();
	writeString(txt, dir);
	std::cout << "Success! \n";
}
/**
 * reads data from user input directory
 */
void read() {
	const std::string dir = getDir();
	std::cout << "Data: \n";
	std::cout << readString(dir) << '\n';
}
/**
 * reads binary data from a file
 */
void readBin() {
	const std::string dir = getDir();
	std::cout << "Binary:";
	// space and newline are handled by the for loop
	const std::vector<bool> bin = readBin(dir);
	for (int i = 0; i < bin.size(); i++) {
		if (!(i % 8)) {
			std::cout << ' ';
		}
		if (!(i % (8 * 8))) {
			std::cout << '\n';
		}
		std::cout << bin[i];
	}
	std::cout << '\n';
}
// /Users/emily/Desktop/test.mscd
int main() {
	// if program should run
	bool run = true;
	while (run) {
		// operation to do
		opcode op = getOp();
		switch (op) {
		case STOP:
			// don't run no more
			run = false;
			break;
		case READ:
			read();
			break;
		case WRITE:
			write();
			break;
		case READBIN:
			readBin();
			break;
		default:
			// error msg
			std::cerr << "Uh oh! Something went wrong.";
			break;
		}
	}
	return 0;
}
