#pragma once

#include <iostream>
#include <regex>

using namespace std;

enum class parsingState
{
	SET,
	READ,
	INVALID,
	QUITE
};

class Parser
{
	public:
		Parser();
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