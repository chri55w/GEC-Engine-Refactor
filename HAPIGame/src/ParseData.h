#include <vector>

#pragma once
class CParseData {

	public:
		static std::vector<int> parseCharVecToInt(std::vector<char> &vecToParse, char seperator);

	private:
		static int combineVecToInt(std::vector<int> data);
};

