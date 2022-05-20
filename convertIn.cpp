/*
 * convertIn.cpp
 *
 *  Created on: May 19, 2022
 *      Author: emily
 */
#include <unordered_map>
#include <string>
#include <vector>

#include "morse.hpp"
/**
 * converts 2 bits of the vector into an int
 */
int bitSegToInt(const std::vector<bool>& bits, const int start) {
	// result
	int result = 0;
	// goes through 2 bits
	for (int i = 0; i < 2; ++i) {
		// shift left 1
		result <<= 1;
		// add current bit
		result += bits[start + i];
	}
	return result;
}
/**
 * convert bools to morse data
 *
 * booleans -> symbols (*, -, end)
 * symbols -> vector of morse strings
 * vector of morse string -> characters
 * characters -> string
 */

/**
 * converts a vector of binary to a vector of symbols
 */
std::vector<char> bitsToSymbols(const std::vector<bool>& bits) {
	std::vector<char> result;
	// list of symbols
	static const char symbols[] = {' ', '*', '-', '/'};
	// goes through bits
	for (int i = 0; i < bits.size(); i += 2) {
		// adds the appropriate symbol
		result.push_back(symbols[bitSegToInt(bits, i)]);
	}
	return result;
}

std::vector<std::string> symbolsToMorseStrings(const std::vector<char>& symbols) {
	// result of the whole thing
	std::vector<std::string> result;
	// stringn of morse characters currently being worked on
	std::string current;
	// loops through symbols
	for (char c: symbols) {
		if (c == ' ') {
			// empty space means end of file
			break;
		// letter break
		} else if (c == '/') {
			// adds string being modified to the list
			result.push_back(current);
			// resets current
			current = "";
		// at this point, c is either '*' or '-'
		} else {
			// adds that character to the string
			current.push_back(c);
		}
	}
	return result;
}
/**
 * converts a vector of morse strings into an alphanumeric string
 */
std::string morseStringsToString(const std::vector<std::string>& strings) {
	// map of stuff
	static const std::unordered_map<std::string, char> map ({
			{"*-", 'a'}, {"-***", 'b'}, {"-*-*", 'c'}, {"-**", 'd'}, {"*",'e'}, {"**-*", 'f'},
			{"--*", 'g'}, {"****", 'h'}, {"**", 'i'}, {"*---", 'j'}, {"-*-", 'k'}, {"*-**", 'l'},
			{"--", 'm' }, {"-*", 'n'}, {"---", 'o'}, {"*--*", 'p'}, {"--*-", 'q'}, {"*-*", 'r'},
			{"***", 's'}, {"-", 't'}, {"**-", 'u'}, {"***-", 'v'}, {"*--", 'w'}, {"-**-", 'x'},
			{"-*--", 'y'}, {"--**", 'z'}, {"-----", '0'}, {"*----", '1'}, {"**---", '2'}, {"***--", '3'},
			{"****-", '4'}, {"*****", '5'}, {"-****", '6'}, {"--***", '7'}, {"---**", '8'}, {"----*", '9'},
			{"", ' '}
		});
	// result of the stuff
	std::string result = "";
	// lopos thru strings
	for (std::string s: strings) {
		// appends the character
		result.push_back(map.at(s));
	}
	return result;
}
/**
 * culmination of all the functions in this file
 */
std::string morseBitsToString(const std::vector<bool>& bits) {
	return morseStringsToString(symbolsToMorseStrings(bitsToSymbols(bits)));
}
