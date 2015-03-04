#include <vector>

#pragma once
class CConfig
{
	public:
		static CConfig &getInstance();
		~CConfig() {};

		std::string getElementAsString(std::string elementName);
		int getElementAsInt(std::string elementName);


	protected:
		CConfig() {};

	private:
		static CConfig *instance_;

		std::vector<int> removeCharFromString(std::string dataString, char charToRemove);
		int parseVecToInt(std::vector<int> data);

		std::string configLoc = "Config/";
};

#define CONFIG CConfig::getInstance()

