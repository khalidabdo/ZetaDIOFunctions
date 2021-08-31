#include "Parser.hpp"

Parser::Parser():mPort{0},mBit{0},mValue{0}
{	
}

void Parser::getInputString()
{
	cout << "Please Enter Input Into Right Format or q to quite: ";
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

	regex setXEnableRegexRule("(set)\\[x,enable\\]");
	if(regex_match(mInput,setXEnableRegexRule))
	{
		mPort = 0;
		mBit = 0;
		return parsingState::ENABLE;
	}

	regex setYEnableRegexRule("(set)\\[y,enable\\]");
	if(regex_match(mInput,setYEnableRegexRule))
	{
		mPort = 0;
		mBit = 1;
		return parsingState::ENABLE;
	}

	regex setXDisableRegexRule("(set)\\[x,disable\\]");
	if(regex_match(mInput,setXDisableRegexRule))
	{
		mPort = 0;
		mBit = 1;
		return parsingState::DISABLE;
	}

	regex setYDisableRegexRule("(set)\\[y,disable\\]");
	if(regex_match(mInput,setYDisableRegexRule))
	{
		mPort = 0;
		mBit = 1;
		return parsingState::DISABLE;
	}

	regex readX("(read)\\[x\\]");
	if(regex_match(mInput,readX))
	{
		mPort = 0;
		mBit = 0;
		mValue = 0;

		return parsingState::READ;
	}

	regex readY("(read)\\[y\\]");
	if(regex_match(mInput,readY))
	{
		mPort = 0;
		mBit = 1;
		mValue = 0;

		return parsingState::READ;
	}

	regex readRegexRule("(read)\\[port\\s[0-7],bit\\s[0-7]\\]");
	if(regex_match(mInput,readRegexRule))
	{
		string stringPort = mInput.substr(10,10);
		string stringBit = mInput.substr(16,16);

		mPort = stoi(stringPort);
		mBit = stoi(stringBit);
		mValue = 0;

		return parsingState::READ;
	}
	
	regex quiteRegexRule("(q)");
	if(regex_match(mInput,quiteRegexRule))
	{
		return parsingState::QUITE;
	}

	mPort = 0;
	mBit = 0;
	mValue = 0;

	return parsingState::INVALID;
}