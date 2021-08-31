#include "Parser.hpp"

Parser::Parser():mPort{0},mBit{0},mValue{0}
{	
}

void Parser::getInputString()
{
	cout << "Please Enter Input Into Right Format: ";
	getline(cin,mInput);
}

uint8_t Parser::getPort()
{
	return mPort;
}

uint8_t Parser::getBit()
{
	return mBit;
}

uint8_t Parser::getValue()
{
	return mValue;
}

parsingState Parser::parsInput()
{
	regex setRegexRule("(set)\\[port\\s[0-7],bit\\s[0-7],bit_value\\s[0-1]\\]");
	if(regex_match(mInput,setRegexRule))
	{
		string stringPort = mInput.substr(9,9);
		string stringBit = mInput.substr(15,15);
		string stringBitValue = mInput.substr(27,27);

		mPort = stoi(stringPort);
		mBit = stoi(stringBit);
		mValue = stoi(stringBitValue);

		return parsingState::SET;
	}
	regex readRegexRule("(read)\\[port\\s[0-7],bit\\s[0-7],bit_value\\s[0-1]\\]");
	if(regex_match(mInput,readRegexRule))
	{
		string stringPort = mInput.substr(10,10);
		string stringBit = mInput.substr(16,16);
		string stringBitValue = mInput.substr(28,28);

		mPort = stoi(stringPort);
		mBit = stoi(stringBit);
		mValue = stoi(stringBitValue);

		return parsingState::READ;
	}
	
	mPort = 0;
	mBit = 0;
	mValue = 0;

	return parsingState::INVALID;
}