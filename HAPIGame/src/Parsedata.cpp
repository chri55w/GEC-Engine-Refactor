#include "ParseData.h"

//Used to parse a vector of chars into integers using a seperator
std::vector<int> CParseData::parseCharVecToInt(std::vector<char> &vecToParse, char seperator) {
	std::vector<int> data;
	std::vector<int> processInts;
	for (char c : vecToParse) {
		if (c != seperator) {
			processInts.push_back(c - '0');
		} else {
			data.push_back(combineVecToInt(processInts));
			processInts.clear();
		}
	}
	return data;
}
//used by the parse character vector function to combine the integers between each seperator
int CParseData::combineVecToInt(std::vector<int> data) {
	int vecSizePower = (int)data.size() - 1;
	int parsedInt = 0;
	for (int vec : data) {
		int multiplier = (int)pow(10, vecSizePower);
		parsedInt += vec * multiplier;
		vecSizePower--;
	}
	return parsedInt;
}