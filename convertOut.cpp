/*
 * morseOut.cpp
 *
 *  Created on: Apr 30, 2022
 *      Author: emily
 */
#include <vector>
#include <unordered_map>
#include <functional>
#include <string>
#include <cctype>

#include "morse.hpp"

/**
 * appends a dot to the specified vector
 */
void dot(std::vector<bool>& vec) {
	// adds a 0, then a 1
	vec.push_back(0);
	vec.push_back(1);
}
/**
 * appends a dash to the specified vector
 */
void dash(std::vector<bool>& vec) {
	// adds a 1, then a 0
	vec.push_back(1);
	vec.push_back(0);
}
/**
 * appends a space to the specified vector
 */
void end(std::vector<bool>& vec) {
	// adds 2 ones
	vec.push_back(1);
	vec.push_back(1);
}
/**
 * turns a character into its morse code representation
 * for example, 'A' -> "*-"
 * non alphanumeric characters are turned into spaces
 */
std::string charToMorseString(char key) {
	// map of char to string containing string representations of morse
	static const std::unordered_map<char, std::string> map ({
			{'a', "*-"}, {'b', "-***"}, {'c', "-*-*"}, {'d', "-**"}, {'e', "*"}, {'f', "**-*"},
			{'g', "--*"}, {'h', "****"}, {'i', "**"}, {'j', "*---"}, {'k', "-*-"}, {'l', "*-**"},
			{'m', "--"}, {'n', "-*"}, {'o', "---"}, {'p', "*--*"}, {'q', "--*-"}, {'r', "*-*"},
			{'s', "***"}, {'t', "-"}, {'u', "**-"}, {'v', "***-"}, {'w', "*--"}, {'x', "-**-"},
			{'y', "-*--"}, {'z', "--**"}, {'0', "-----"}, {'1', "*----"}, {'2', "**---"}, {'3', "***--"},
			{'4', "****-"}, {'5', "*****"}, {'6', "-****"}, {'7', "--***"}, {'8', "---**"}, {'9', "----*"},
			{' ', ""}
		});
	// if the key isn't alphanumeric
	if (!isalnum(key)) {
		// set it to space
		key = ' ';
	}
	// if the key is uppercase
	if (isupper(key)) {
		// set it to lowercase
		key = tolower(key);
	}
	// returns the string mapped to the key
	return map.at(key);
}
/**
 * converts a morse string into the binary representation of it
 * includes the separator at the end
 */
std::vector<bool> morseStringToMorseBits(const std::string& str) {
	// stores the result
	std::vector<bool> result;
	// a map of char to function, specifically functions that take in vector<bool>&  and output void
	static const std::unordered_map<char, std::function<void(std::vector<bool>&)>> map ({{'*', dot}, {'-', dash}});
	// loops through the string
	for (char c: str) {
		// calls {the function mapped to current character} on result
		map.at(c)(result);
	}
	// adds the space character to the end
	end(result);
	return result;
}
/**
 * joins together two vectors of bool. the first parameter is the one
 * that gets modified
 */
void joinBits(std::vector<bool>& start, const std::vector<bool>& addition) {
	for (bool b: addition) {
		start.push_back(b);
	}
}
/**
 * converts a string into the morse bits required to represent it
 */
std::vector<bool> stringToMorseBits(const std::string& str) {
	std::vector<bool> result;
	for (char c: str) {
		joinBits(result, morseStringToMorseBits(charToMorseString(c)));
	}
	return result;
}
/**
 * creates a humanly readable string representation of a vector
 */
std::string morseBitsToHumanString(const std::vector<bool>& vec) {
	// string to store the result
	std::string result = "";
	// loops through the vector
	for (int i = 0; i < vec.size(); ++i) {
		// appends the data to the result
		result.append(to_string(vec[i]));
		// if it's an odd number, put a space
		if (i % 2) {
			result.append(" ");
		}
	}
	return result;
}
