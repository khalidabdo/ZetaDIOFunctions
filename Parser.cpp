#include "Parser.hpp"

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
		string port = mInput.substr(9,9);
		string bit = mInput.substr(15,15);
		string bit_value = mInput.substr(27,27);

		mPort = static_cast<uint8_t>(stoi(port));
		mBit = static_cast<uint8_t>(stoi(bit));
		mValue = static_cast<uint8_t>(stoi(bit_value));

		return parsingState::SET;
	}
	regex readRegexRule("(read)\\[port\\s[0-7],bit\\s[0-7],bit_value\\s[0-1]\\]");
	if(regex_match(mInput,readRegexRule))
	{
		string port = mInput.substr(10,10);
		string bit = mInput.substr(15,15);
		string bit_value = mInput.substr(28,28);

		mPort = static_cast<uint8_t>(stoi(port));
		mBit = static_cast<uint8_t>(stoi(bit));
		mValue = static_cast<uint8_t>(stoi(bit_value));

		return parsingState::READ;
	}
	
	mPort = 0;
	mBit = 0;
	mValue = 0;

	return parsingState::INVALID;
}