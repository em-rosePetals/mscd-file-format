/*
 * read.cpp
 *
 *  Created on: May 15, 2022
 *      Author: emily
 */
#include <fstream>
#include <iostream>
#include <vector>

#include "morse.hpp"
/**
 * reads data from a file and turns it into a vector of char
 */
std::vector<char> fileToData(const std::string& dir) {
	// size of the file
	std::streampos size;
	// memory block for containing file
	char* memblock;
	// file input
	std::ifstream file;
	// opens file for input at the end in binary
	file.open(dir, std::ios::in | std::ios::ate | std::ios::binary);
	// stores all the chars in a much more convenient format than a char* and int
	std::vector<char> result;
	// if file is opened
	if (file.is_open()) {
		// sets size to the size of the file
		size = file.tellg();
		// allocates memory for the file
		memblock = new char[size];
		// puts cursor at beginning of file
		file.seekg(0, std::ios::beg);
		// reads data from file into memory block
		file.read(memblock, size);
		// prevents resource leak
		file.close();
		// loops through array
		for (int i = 0; i < size; i++) {
			// adds data from array into memory
			result.push_back(memblock[i]);
		}
		// deletes the memory allocated for that array
		delete[] memblock;
	} else {
		// error message
		std::cerr << "uh oh";
		// makes it say __bad__
		for (char c: "__bad__") {
			result.push_back(c);
		}
	}
	return result;
}
/**
 * converts a vector of char into a vector of binary with the corresponding data
 */
std::vector<bool> dataToBits(const std::vector<char>& chars) {
	std::vector<bool> result;
	// loops through vector
	for (char c: chars) {
		// loops [0, 8)
		for (int i = 0; i < 8; ++i) {
			// gets a bit from the character and puts it into the vector
			result.push_back(c >> (7 - i) & 1);
		}
	}
	return result;
}

std::string readString(const std::string& dir) {
	return morseBitsToString(dataToBits(fileToData(dir)));
}

