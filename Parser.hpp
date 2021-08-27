#pragma once

#include <iostream>
#include <string>
#include <regex>
#include <sstream>

using namespace std;

enum class parsingState
{
	SET,
	READ,
	INVALID
};

class Parser
{
	public:
		Parser():mPort{0},mBit{0},mValue{0}
		{	
		}
		void getInputString();
		uint8_t getPort();
		uint8_t getBit();
		uint8_t getValue();
		parsingState parsInput();

	private:
		uint8_t mPort;
		uint8_t mBit;
		uint8_t mValue;
		string mInput;
};