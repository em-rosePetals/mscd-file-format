/*
 * writeOut.cpp
 *
 *  Created on: May 3, 2022
 *      Author: emily
 */
#include <iostream>
#include <fstream>
#include <vector>

#include "morse.hpp"

/**
 * pads a vector<bool> with 0 values, in order to make it divisible by 8
 */
void pad(std::vector<bool>& vect) {
	while (vect.size() % 8) {
		vect.push_back(0);
	}
}
/**
 * takes a segment of the vector (from start to start + 8)
 * and converts it into a character
 */
char bitSegmentToChar(const std::vector<bool>& vect, const int start) {
	// all zero data
	char result = '\0';
	// loops through the vector from the start to the start plus 8
	for (int i = start; i < start + 8; i++) {
		// shifts the character left one, then adds the new data we need
		result = (result << 1) + vect[i];
	}
	// returns result
	return result;
}
/**
 * converts a vector of binary into a sequence of chars.
 * includes the header
 */
std::vector<char> morseBitsToChars(const std::vector<bool>& vect) {
	// size of the vector
	const int size = vect.size();
	// size of the array of char
	const int dataSize = size / 8;
	// array of char
	std::vector<char> data(dataSize);
	// loops through the array
	for (int i = 0; i < dataSize; ++i) {
		// sets current index to the char value
		data[i] = bitSegmentToChar(vect, i * 8);
	}
	// returns data
	return data;
}
/**
 * writes a string into the specified file directory
 */
void writeString(const std::string& str, const std::string& dir) {
	// binary data
	std::vector<bool> bits = stringToMorseBits(str);
	// adds zeroes at the end so bits.size() % 8 == 0
	pad(bits);
	// vector of char
	std::vector<char> data = morseBitsToChars(bits);
	// file writer
	std::ofstream file;
	// opens it with the directory and flags for output, append, and binary
	file.open(dir, std::ios::out | std::ios::trunc | std::ios::binary);
	// checks if file is open
	if (file.is_open()) {
		// writes data to file
		file.write(&data[0], data.size());
	} else {
		std::cout << "uh oh!";
	}
}
