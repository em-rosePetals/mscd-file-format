
#ifndef MORSE_HPP_
#define MORSE_HPP_

void writeString(const std::string& str, const std::string& dir);
std::vector<bool> stringToMorseBits(const std::string& str);

std::vector<bool> readBin(const std::string& dir);
std::string readString(const std::string& dir);
std::string morseBitsToString(const std::vector<bool>& bits);

#endif /* MORSE_HPP_ */
